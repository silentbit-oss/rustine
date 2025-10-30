png_uint_16 png_get_uint_16(png_const_bytep buf)
{
  unsigned int val = (((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)));
  return (png_uint_16) val;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
***/


png_uint_32 png_get_uint_32(png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  return uval;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
***/


png_int_32 png_get_int_32(png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if ((uval & 0x80000000) == 0)
  {
    return (png_int_32) uval;
  }
  uval = (uval ^ 0xffffffff) + 1;
  if ((uval & 0x80000000) == 0)
  {
    return -((png_int_32) uval);
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
***/


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


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_read_data(png_structrp png_ptr, png_bytep data, size_t length)
{
  (void) 0;
  if (png_ptr->read_data_fn != 0)
  {
    (*png_ptr->read_data_fn)(png_ptr, data, length);
  }
  else
    png_error(png_ptr, "Call to NULL read function");
}


----------------------------
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


int png_crc_error(png_structrp png_ptr)
{
  png_byte crc_bytes[4];
  png_uint_32 crc;
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
  png_ptr->io_state = 0x0001 | 0x0080;
  png_read_data(png_ptr, crc_bytes, 4);
  if (need_crc != 0)
  {
    crc = (((((png_uint_32) (*crc_bytes)) << 24) + (((png_uint_32) (*(crc_bytes + 1))) << 16)) + (((png_uint_32) (*(crc_bytes + 2))) << 8)) + ((png_uint_32) (*(crc_bytes + 3)));
    return (int) (crc != png_ptr->crc);
  }
  else
    return 0;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_read_data(png_structrp png_ptr, png_bytep data, size_t length)
{
  (void) 0;
  if (png_ptr->read_data_fn != 0)
  {
    (*png_ptr->read_data_fn)(png_ptr, data, length);
  }
  else
    png_error(png_ptr, "Call to NULL read function");
}


----------------------------
***/


void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_read_data(png_structrp png_ptr, png_bytep data, size_t length)
{
  (void) 0;
  if (png_ptr->read_data_fn != 0)
  {
    (*png_ptr->read_data_fn)(png_ptr, data, length);
  }
  else
    png_error(png_ptr, "Call to NULL read function");
}


----------------------------
typedef png_byte *png_bytep
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
int png_crc_error(png_structrp png_ptr)
{
  png_byte crc_bytes[4];
  png_uint_32 crc;
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
  png_ptr->io_state = 0x0001 | 0x0080;
  png_read_data(png_ptr, crc_bytes, 4);
  if (need_crc != 0)
  {
    crc = (((((png_uint_32) (*crc_bytes)) << 24) + (((png_uint_32) (*(crc_bytes + 1))) << 16)) + (((png_uint_32) (*(crc_bytes + 2))) << 8)) + ((png_uint_32) (*(crc_bytes + 3)));
    return (int) (crc != png_ptr->crc);
  }
  else
    return 0;
}


----------------------------
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
***/


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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (png_uint_32) 0x7fffffffL;
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (png_ptr->chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_alloc_size_t idat_limit = (png_uint_32) 0x7fffffffL;
    size_t row_factor = (((((size_t) png_ptr->width) * ((size_t) png_ptr->channels)) * ((png_ptr->bit_depth > 8) ? (2) : (1))) + 1) + ((png_ptr->interlaced) ? (6) : (0));
    if (png_ptr->height > (((png_uint_32) (-1)) / row_factor))
    {
      idat_limit = (png_uint_32) 0x7fffffffL;
    }
    else
      idat_limit = png_ptr->height * row_factor;
    row_factor = (row_factor > 32566) ? (32566) : (row_factor);
    idat_limit += 6 + (5 * ((idat_limit / row_factor) + 1));
    idat_limit = (idat_limit < ((png_uint_32) 0x7fffffffL)) ? (idat_limit) : ((png_uint_32) 0x7fffffffL);
    limit = (limit < idat_limit) ? (idat_limit) : (limit);
  }
  if (length > limit)
  {
    (void) 0;
    png_benign_error(png_ptr, "chunk data is too large");
  }
}


/*** DEPENDENCIES:
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
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if (uval > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "PNG unsigned integer out of range");
  }
  return uval;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef const png_byte *png_const_bytep
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


void png_check_chunk_name(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  int i;
  png_uint_32 cn = chunk_name;
  (void) 0;
  for (i = 1; i <= 4; i += 1)
  {
    int c = cn & 0xff;
    if (((c < 65) || (c > 122)) || ((c > 90) && (c < 97)))
    {
      png_chunk_error(png_ptr, "invalid chunk type");
    }
    cn >>= 8;
  }

}


/*** DEPENDENCIES:
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
typedef unsigned int png_uint_32
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


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


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (png_uint_32) 0x7fffffffL;
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (png_ptr->chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_alloc_size_t idat_limit = (png_uint_32) 0x7fffffffL;
    size_t row_factor = (((((size_t) png_ptr->width) * ((size_t) png_ptr->channels)) * ((png_ptr->bit_depth > 8) ? (2) : (1))) + 1) + ((png_ptr->interlaced) ? (6) : (0));
    if (png_ptr->height > (((png_uint_32) (-1)) / row_factor))
    {
      idat_limit = (png_uint_32) 0x7fffffffL;
    }
    else
      idat_limit = png_ptr->height * row_factor;
    row_factor = (row_factor > 32566) ? (32566) : (row_factor);
    idat_limit += 6 + (5 * ((idat_limit / row_factor) + 1));
    idat_limit = (idat_limit < ((png_uint_32) 0x7fffffffL)) ? (idat_limit) : ((png_uint_32) 0x7fffffffL);
    limit = (limit < idat_limit) ? (idat_limit) : (limit);
  }
  if (length > limit)
  {
    (void) 0;
    png_benign_error(png_ptr, "chunk data is too large");
  }
}


----------------------------
void png_reset_crc(png_structrp png_ptr)
{
  png_ptr->crc = (png_uint_32) crc32(0, 0, 0);
}


----------------------------
png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if (uval > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "PNG unsigned integer out of range");
  }
  return uval;
}


----------------------------
void png_check_chunk_name(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  int i;
  png_uint_32 cn = chunk_name;
  (void) 0;
  for (i = 1; i <= 4; i += 1)
  {
    int c = cn & 0xff;
    if (((c < 65) || (c > 122)) || ((c > 90) && (c < 97)))
    {
      png_chunk_error(png_ptr, "invalid chunk type");
    }
    cn >>= 8;
  }

}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_read_data(png_structrp png_ptr, png_bytep data, size_t length)
{
  (void) 0;
  if (png_ptr->read_data_fn != 0)
  {
    (*png_ptr->read_data_fn)(png_ptr, data, length);
  }
  else
    png_error(png_ptr, "Call to NULL read function");
}


----------------------------
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


----------------------------
***/


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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
typedef png_info *png_inforp
----------------------------
png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if (uval > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "PNG unsigned integer out of range");
  }
  return uval;
}


----------------------------
***/


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
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


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
typedef png_color *png_colorp
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


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
typedef unsigned int png_uint_32
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
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
typedef png_info *png_inforp
----------------------------
***/


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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef unsigned short png_uint_16
----------------------------
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
typedef png_info *png_inforp
----------------------------
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


----------------------------
***/


static int png_cache_unknown_chunk(png_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (size_t) (-1);
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
    png_ptr->unknown_chunk.data = 0;
  }
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (length <= limit)
  {
    (void) (((void) ((((char *) png_ptr->unknown_chunk.name)[0] = (char) ((png_ptr->chunk_name >> 24) & 0xff), ((char *) png_ptr->unknown_chunk.name)[1] = (char) ((png_ptr->chunk_name >> 16) & 0xff), ((char *) png_ptr->unknown_chunk.name)[2] = (char) ((png_ptr->chunk_name >> 8) & 0xff), ((char *) png_ptr->unknown_chunk.name)[3] = (char) (png_ptr->chunk_name & 0xff))), ((char *) png_ptr->unknown_chunk.name)[4] = 0));
    png_ptr->unknown_chunk.size = (size_t) length;
    png_ptr->unknown_chunk.location = (png_byte) png_ptr->mode;
    if (length == 0)
    {
      png_ptr->unknown_chunk.data = 0;
    }
    else
    {
      png_ptr->unknown_chunk.data = png_malloc_warn(png_ptr, length);
    }
  }
  if ((png_ptr->unknown_chunk.data == 0) && (length > 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "unknown chunk exceeds memory limits");
    return 0;
  }
  else
  {
    if (length > 0)
    {
      png_crc_read(png_ptr, png_ptr->unknown_chunk.data, length);
    }
    png_crc_finish(png_ptr, 0);
    return 1;
  }
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
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
typedef unsigned int png_uint_32
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
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
***/


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
typedef unsigned int png_uint_32
----------------------------
typedef struct png_info_def png_info
----------------------------
static int png_cache_unknown_chunk(png_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (size_t) (-1);
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
    png_ptr->unknown_chunk.data = 0;
  }
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (length <= limit)
  {
    (void) (((void) ((((char *) png_ptr->unknown_chunk.name)[0] = (char) ((png_ptr->chunk_name >> 24) & 0xff), ((char *) png_ptr->unknown_chunk.name)[1] = (char) ((png_ptr->chunk_name >> 16) & 0xff), ((char *) png_ptr->unknown_chunk.name)[2] = (char) ((png_ptr->chunk_name >> 8) & 0xff), ((char *) png_ptr->unknown_chunk.name)[3] = (char) (png_ptr->chunk_name & 0xff))), ((char *) png_ptr->unknown_chunk.name)[4] = 0));
    png_ptr->unknown_chunk.size = (size_t) length;
    png_ptr->unknown_chunk.location = (png_byte) png_ptr->mode;
    if (length == 0)
    {
      png_ptr->unknown_chunk.data = 0;
    }
    else
    {
      png_ptr->unknown_chunk.data = png_malloc_warn(png_ptr, length);
    }
  }
  if ((png_ptr->unknown_chunk.data == 0) && (length > 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "unknown chunk exceeds memory limits");
    return 0;
  }
  else
  {
    if (length > 0)
    {
      png_crc_read(png_ptr, png_ptr->unknown_chunk.data, length);
    }
    png_crc_finish(png_ptr, 0);
    return 1;
  }
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
typedef png_info *png_inforp
----------------------------
***/


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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
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
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


int png_zlib_inflate(png_structrp png_ptr, int flush)
{
  if (png_ptr->zstream_start && (png_ptr->zstream.avail_in > 0))
  {
    if (((*png_ptr->zstream.next_in) >> 4) > 7)
    {
      png_ptr->zstream.msg = "invalid window size (libpng)";
      return -3;
    }
    png_ptr->zstream_start = 0;
  }
  return inflate(&png_ptr->zstream, flush);
}


/*** DEPENDENCIES:
int inflate(z_streamp strm, int flush)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  const unsigned char *next;
  unsigned int next_idx = 0;
  unsigned char *put;
  unsigned int put_idx = 0;
  unsigned have;
  unsigned left;
  unsigned long hold;
  unsigned bits;
  unsigned in;
  unsigned out;
  unsigned copy;
  unsigned char *from;
  unsigned int from_idx = 0;
  code here;
  code last;
  unsigned len;
  int ret;
  static const unsigned short order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  if ((inflateStateCheck(strm) || (strm->next_out == 0)) || ((strm->next_in == 0) && (strm->avail_in != 0)))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->mode == TYPE)
  {
    state->mode = TYPEDO;
  }
  do
  {
    put_idx = strm->next_out;
    left = strm->avail_out;
    next_idx = strm->next_in;
    have = strm->avail_in;
    hold = state->hold;
    bits = state->bits;
  }
  while (0);
  in = have;
  out = left;
  ret = 0;
  for (;;)
  {
    helper_inflate_1(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, &out, &copy, &from_idx, &here, &last, &len, &ret, flush, state, next, put, from, order);
  }

  inf_leave:
  do
  {
    strm->next_out = &put[put_idx];
    strm->avail_out = left;
    strm->next_in = &next[next_idx];
    strm->avail_in = have;
    state->hold = hold;
    state->bits = bits;
  }
  while (0);

  if (state->wsize || (((out != strm->avail_out) && (state->mode < BAD)) && ((state->mode < CHECK) || (flush != 4))))
  {
    if (updatewindow(strm, strm->next_out, out - strm->avail_out))
    {
      state->mode = MEM;
      return -4;
    }
  }
  in -= strm->avail_in;
  out -= strm->avail_out;
  strm->total_in += in;
  strm->total_out += out;
  state->total += out;
  if ((state->wrap & 4) && out)
  {
    strm->adler = (state->check = adler32(state->check, strm->next_out - out, out));
  }
  strm->data_type = ((((int) state->bits) + ((state->last) ? (64) : (0))) + ((state->mode == TYPE) ? (128) : (0))) + (((state->mode == LEN_) || (state->mode == COPY_)) ? (256) : (0));
  if ((((in == 0) && (out == 0)) || (flush == 4)) && (ret == 0))
  {
    ret = -5;
  }
  return ret;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static png_bytep png_read_buffer(png_structrp png_ptr, png_alloc_size_t new_size, int warn)
{
  png_bytep buffer = png_ptr->read_buffer;
  if ((buffer != 0) && (new_size > png_ptr->read_buffer_size))
  {
    png_ptr->read_buffer = 0;
    png_ptr->read_buffer_size = 0;
    png_free(png_ptr, buffer);
    buffer = 0;
  }
  if (buffer == 0)
  {
    buffer = png_malloc_base(png_ptr, new_size);
    if (buffer != 0)
    {
      memset(buffer, 0, new_size);
      png_ptr->read_buffer = buffer;
      png_ptr->read_buffer_size = new_size;
    }
    else
      if (warn < 2)
    {
      if (warn != 0)
      {
        png_chunk_warning(png_ptr, "insufficient memory to read chunk");
      }
      else
        png_chunk_error(png_ptr, "insufficient memory to read chunk");
    }
  }
  return buffer;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
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
typedef unsigned char png_byte
----------------------------
void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
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


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
void helper_helper_png_read_IDAT_data_1_1(png_structrp * const png_ptr_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  uInt avail_in;
  png_bytep buffer;
  while (png_ptr->idat_size == 0)
  {
    png_crc_finish(png_ptr, 0);
    png_ptr->idat_size = png_read_chunk_header(png_ptr);
    if (png_ptr->chunk_name != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      png_error(png_ptr, "Not enough image data");
    }
  }

  avail_in = png_ptr->IDAT_read_size;
  if (avail_in > png_ptr->idat_size)
  {
    avail_in = (uInt) png_ptr->idat_size;
  }
  buffer = png_read_buffer(png_ptr, avail_in, 0);
  png_crc_read(png_ptr, buffer, avail_in);
  png_ptr->idat_size -= avail_in;
  png_ptr->zstream.next_in = buffer;
  png_ptr->zstream.avail_in = avail_in;
  *png_ptr_ref = png_ptr;
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
typedef unsigned char png_byte
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
static png_bytep png_read_buffer(png_structrp png_ptr, png_alloc_size_t new_size, int warn)
{
  png_bytep buffer = png_ptr->read_buffer;
  if ((buffer != 0) && (new_size > png_ptr->read_buffer_size))
  {
    png_ptr->read_buffer = 0;
    png_ptr->read_buffer_size = 0;
    png_free(png_ptr, buffer);
    buffer = 0;
  }
  if (buffer == 0)
  {
    buffer = png_malloc_base(png_ptr, new_size);
    if (buffer != 0)
    {
      memset(buffer, 0, new_size);
      png_ptr->read_buffer = buffer;
      png_ptr->read_buffer_size = new_size;
    }
    else
      if (warn < 2)
    {
      if (warn != 0)
      {
        png_chunk_warning(png_ptr, "insufficient memory to read chunk");
      }
      else
        png_chunk_error(png_ptr, "insufficient memory to read chunk");
    }
  }
  return buffer;
}


----------------------------
typedef unsigned int uInt
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
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
void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}


----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'avail_out_ref is a mutable refrence to png_alloc_size_t']
void helper_png_read_IDAT_data_1(png_structrp * const png_ptr_ref, png_alloc_size_t * const avail_out_ref, png_bytep output)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_alloc_size_t avail_out = *avail_out_ref;
  int ret;
  png_byte tmpbuf[1024];
  if (png_ptr->zstream.avail_in == 0)
  {
    helper_helper_png_read_IDAT_data_1_1(&png_ptr);
  }
  if (output != 0)
  {
    uInt out = (uInt) (-1);
    if (out > avail_out)
    {
      out = (uInt) avail_out;
    }
    avail_out -= out;
    png_ptr->zstream.avail_out = out;
  }
  else
  {
    png_ptr->zstream.next_out = tmpbuf;
    png_ptr->zstream.avail_out = sizeof(tmpbuf);
  }
  ret = png_zlib_inflate(png_ptr, 0);
  if (output != 0)
  {
    avail_out += png_ptr->zstream.avail_out;
  }
  else
    avail_out += (sizeof(tmpbuf)) - png_ptr->zstream.avail_out;
  png_ptr->zstream.avail_out = 0;
  if (ret == 1)
  {
    png_ptr->zstream.next_out = 0;
    png_ptr->mode |= 0x08;
    png_ptr->flags |= 0x0008U;
    if ((png_ptr->zstream.avail_in > 0) || (png_ptr->idat_size > 0))
    {
      png_chunk_benign_error(png_ptr, "Extra compressed data");
    }
    break;
  }
  if (ret != 0)
  {
    png_zstream_error(png_ptr, ret);
    if (output != 0)
    {
      png_chunk_error(png_ptr, png_ptr->zstream.msg);
    }
    else
    {
      png_chunk_benign_error(png_ptr, png_ptr->zstream.msg);
      return;
    }
  }
  *png_ptr_ref = png_ptr;
  *avail_out_ref = avail_out;
}


/*** DEPENDENCIES:
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


----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned char png_byte
----------------------------
int png_zlib_inflate(png_structrp png_ptr, int flush)
{
  if (png_ptr->zstream_start && (png_ptr->zstream.avail_in > 0))
  {
    if (((*png_ptr->zstream.next_in) >> 4) > 7)
    {
      png_ptr->zstream.msg = "invalid window size (libpng)";
      return -3;
    }
    png_ptr->zstream_start = 0;
  }
  return inflate(&png_ptr->zstream, flush);
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
typedef unsigned int uInt
----------------------------
void helper_helper_png_read_IDAT_data_1_1(png_structrp * const png_ptr_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  uInt avail_in;
  png_bytep buffer;
  while (png_ptr->idat_size == 0)
  {
    png_crc_finish(png_ptr, 0);
    png_ptr->idat_size = png_read_chunk_header(png_ptr);
    if (png_ptr->chunk_name != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      png_error(png_ptr, "Not enough image data");
    }
  }

  avail_in = png_ptr->IDAT_read_size;
  if (avail_in > png_ptr->idat_size)
  {
    avail_in = (uInt) png_ptr->idat_size;
  }
  buffer = png_read_buffer(png_ptr, avail_in, 0);
  png_crc_read(png_ptr, buffer, avail_in);
  png_ptr->idat_size -= avail_in;
  png_ptr->zstream.next_in = buffer;
  png_ptr->zstream.avail_in = avail_in;
  *png_ptr_ref = png_ptr;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
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
***/


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


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
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
void helper_png_read_IDAT_data_1(png_structrp * const png_ptr_ref, png_alloc_size_t * const avail_out_ref, png_bytep output)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_alloc_size_t avail_out = *avail_out_ref;
  int ret;
  png_byte tmpbuf[1024];
  if (png_ptr->zstream.avail_in == 0)
  {
    helper_helper_png_read_IDAT_data_1_1(&png_ptr);
  }
  if (output != 0)
  {
    uInt out = (uInt) (-1);
    if (out > avail_out)
    {
      out = (uInt) avail_out;
    }
    avail_out -= out;
    png_ptr->zstream.avail_out = out;
  }
  else
  {
    png_ptr->zstream.next_out = tmpbuf;
    png_ptr->zstream.avail_out = sizeof(tmpbuf);
  }
  ret = png_zlib_inflate(png_ptr, 0);
  if (output != 0)
  {
    avail_out += png_ptr->zstream.avail_out;
  }
  else
    avail_out += (sizeof(tmpbuf)) - png_ptr->zstream.avail_out;
  png_ptr->zstream.avail_out = 0;
  if (ret == 1)
  {
    png_ptr->zstream.next_out = 0;
    png_ptr->mode |= 0x08;
    png_ptr->flags |= 0x0008U;
    if ((png_ptr->zstream.avail_in > 0) || (png_ptr->idat_size > 0))
    {
      png_chunk_benign_error(png_ptr, "Extra compressed data");
    }
    break;
  }
  if (ret != 0)
  {
    png_zstream_error(png_ptr, ret);
    if (output != 0)
    {
      png_chunk_error(png_ptr, png_ptr->zstream.msg);
    }
    else
    {
      png_chunk_benign_error(png_ptr, png_ptr->zstream.msg);
      return;
    }
  }
  *png_ptr_ref = png_ptr;
  *avail_out_ref = avail_out;
}


----------------------------
***/


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
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
void helper_png_read_start_row_1(png_structrp * const png_ptr_ref, size_t row_bytes)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_free(png_ptr, png_ptr->big_row_buf);
  png_free(png_ptr, png_ptr->big_prev_row);
  if (png_ptr->interlaced != 0)
  {
    png_ptr->big_row_buf = (png_bytep) png_calloc(png_ptr, row_bytes + 48);
  }
  else
    png_ptr->big_row_buf = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
  png_ptr->big_prev_row = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
  {
    png_bytep temp = png_ptr->big_row_buf + 32;
    size_t extra = ((size_t) temp) & 0x0f;
    png_ptr->row_buf = (temp - extra) - 1;
    temp = png_ptr->big_prev_row + 32;
    extra = ((size_t) temp) & 0x0f;
    png_ptr->prev_row = (temp - extra) - 1;
  }
  png_ptr->old_big_row_buf_size = row_bytes + 48;
  *png_ptr_ref = png_ptr;
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
typedef unsigned char png_byte
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
typedef png_byte *png_bytep
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
***/


static int png_inflate_claim(png_structrp png_ptr, png_uint_32 owner)
{
  if (png_ptr->zowner != 0)
  {
    char msg[64];
    (void) ((((char *) msg)[0] = (char) ((png_ptr->zowner >> 24) & 0xff), ((char *) msg)[1] = (char) ((png_ptr->zowner >> 16) & 0xff), ((char *) msg)[2] = (char) ((png_ptr->zowner >> 8) & 0xff), ((char *) msg)[3] = (char) (png_ptr->zowner & 0xff)));
    (void) png_safecat(msg, sizeof(msg), 4, " using zstream");
    png_chunk_warning(png_ptr, msg);
    png_ptr->zowner = 0;
  }
  {
    int ret;
    int window_bits = 0;
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zstream.next_out = 0;
    png_ptr->zstream.avail_out = 0;
    if ((png_ptr->flags & 0x0002U) != 0)
    {
      ret = inflateReset2(&png_ptr->zstream, window_bits);
    }
    else
    {
      ret = inflateInit2_(&png_ptr->zstream, window_bits, "1.3-optipng", (int) (sizeof(z_stream)));
      if (ret == 0)
      {
        png_ptr->flags |= 0x0002U;
      }
    }
    if (ret == 0)
    {
      png_ptr->zowner = owner;
    }
    else
      png_zstream_error(png_ptr, ret);
    return ret;
  }
}


/*** DEPENDENCIES:
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


----------------------------
int inflateReset2(z_streamp strm, int windowBits)
{
  int wrap;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (windowBits < 0)
  {
    if (windowBits < (-15))
    {
      return -2;
    }
    wrap = 0;
    windowBits = -windowBits;
  }
  else
  {
    wrap = (windowBits >> 4) + 5;
  }
  if (windowBits && ((windowBits < 8) || (windowBits > 15)))
  {
    return -2;
  }
  if ((state->window != 0) && (state->wbits != ((unsigned) windowBits)))
  {
    (*strm->zfree)(strm->opaque, (voidpf) state->window);
    state->window = 0;
  }
  state->wrap = wrap;
  state->wbits = (unsigned) windowBits;
  return inflateReset(strm);
}


----------------------------
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
typedef unsigned int png_uint_32
----------------------------
void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}


----------------------------
int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size)
{
  int ret;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((version == 0) || (version[0] != "1.3-optipng"[0])) || (stream_size != ((int) (sizeof(z_stream)))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  state_idx = (struct inflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(struct inflate_state));
  if ((&state[state_idx]) == 0)
  {
    return -4;
  }
  ;
  strm->state = (struct internal_state *) state;
  state->strm = strm;
  state->window = 0;
  state->mode = HEAD;
  ret = inflateReset2(strm, windowBits);
  if (ret != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state);
    strm->state = 0;
  }
  return ret;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


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


/*** DEPENDENCIES:
void helper_png_read_start_row_1(png_structrp * const png_ptr_ref, size_t row_bytes)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_free(png_ptr, png_ptr->big_row_buf);
  png_free(png_ptr, png_ptr->big_prev_row);
  if (png_ptr->interlaced != 0)
  {
    png_ptr->big_row_buf = (png_bytep) png_calloc(png_ptr, row_bytes + 48);
  }
  else
    png_ptr->big_row_buf = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
  png_ptr->big_prev_row = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
  {
    png_bytep temp = png_ptr->big_row_buf + 32;
    size_t extra = ((size_t) temp) & 0x0f;
    png_ptr->row_buf = (temp - extra) - 1;
    temp = png_ptr->big_prev_row + 32;
    extra = ((size_t) temp) & 0x0f;
    png_ptr->prev_row = (temp - extra) - 1;
  }
  png_ptr->old_big_row_buf_size = row_bytes + 48;
  *png_ptr_ref = png_ptr;
}


----------------------------
typedef unsigned char png_byte
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
static int png_inflate_claim(png_structrp png_ptr, png_uint_32 owner)
{
  if (png_ptr->zowner != 0)
  {
    char msg[64];
    (void) ((((char *) msg)[0] = (char) ((png_ptr->zowner >> 24) & 0xff), ((char *) msg)[1] = (char) ((png_ptr->zowner >> 16) & 0xff), ((char *) msg)[2] = (char) ((png_ptr->zowner >> 8) & 0xff), ((char *) msg)[3] = (char) (png_ptr->zowner & 0xff)));
    (void) png_safecat(msg, sizeof(msg), 4, " using zstream");
    png_chunk_warning(png_ptr, msg);
    png_ptr->zowner = 0;
  }
  {
    int ret;
    int window_bits = 0;
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zstream.next_out = 0;
    png_ptr->zstream.avail_out = 0;
    if ((png_ptr->flags & 0x0002U) != 0)
    {
      ret = inflateReset2(&png_ptr->zstream, window_bits);
    }
    else
    {
      ret = inflateInit2_(&png_ptr->zstream, window_bits, "1.3-optipng", (int) (sizeof(z_stream)));
      if (ret == 0)
      {
        png_ptr->flags |= 0x0002U;
      }
    }
    if (ret == 0)
    {
      png_ptr->zowner = owner;
    }
    else
      png_zstream_error(png_ptr, ret);
    return ret;
  }
}


----------------------------
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


----------------------------
***/


void helper_helper_png_do_read_interlace_1_1(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  size_t pixel_bytes = row_info->pixel_depth >> 3;
  png_bytep sp = row + (((size_t) (row_info->width - 1)) * pixel_bytes);
  png_bytep dp = row + (((size_t) (final_width - 1)) * pixel_bytes);
  int jstop = (int) png_pass_inc[pass];
  png_uint_32 i;
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v[8];
    int j;
    memcpy(v, sp, pixel_bytes);
    for (j = 0; j < jstop; j += 1)
    {
      memcpy(dp, v, pixel_bytes);
      dp -= pixel_bytes;
    }

    sp -= pixel_bytes;
  }

  break;
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void helper_helper_png_do_read_interlace_1_3(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 3));
  png_bytep dp = row + ((size_t) ((final_width - 1) >> 3));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  int jstop = (int) png_pass_inc[pass];
  png_byte v;
  png_uint_32 i;
  int j;
  {
    sshift = 7 - ((row_info->width + 7) & 0x07);
    dshift = 7 - ((final_width + 7) & 0x07);
    s_start = 0;
    s_end = 7;
    s_inc = 1;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    v = (png_byte) (((*sp) >> sshift) & 0x01);
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0x7f7f >> (7 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void helper_helper_png_do_read_interlace_1_2(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 1));
  png_bytep dp = row + ((size_t) ((final_width - 1) >> 1));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  png_uint_32 i;
  int jstop = (int) png_pass_inc[pass];
  {
    sshift = (1 - ((row_info->width + 1) & 0x01)) << 2;
    dshift = (1 - ((final_width + 1) & 0x01)) << 2;
    s_start = 0;
    s_end = 4;
    s_inc = 4;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v = (png_byte) (((*sp) >> sshift) & 0x0f);
    int j;
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0xf0f >> (4 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void helper_helper_png_do_read_interlace_1_4(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((png_uint_32) ((row_info->width - 1) >> 2));
  png_bytep dp = row + ((png_uint_32) ((final_width - 1) >> 2));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  int jstop = (int) png_pass_inc[pass];
  png_uint_32 i;
  {
    sshift = (3 - ((row_info->width + 3) & 0x03)) << 1;
    dshift = (3 - ((final_width + 3) & 0x03)) << 1;
    s_start = 0;
    s_end = 6;
    s_inc = 2;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v;
    int j;
    v = (png_byte) (((*sp) >> sshift) & 0x03);
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0x3f3f >> (6 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['row_info_ref is a mutable refrence to png_row_infop']
void helper_png_do_read_interlace_1(png_row_infop * const row_info_ref, png_bytep row, int pass, static const unsigned int png_pass_inc[7])
{
  png_row_infop row_info = *row_info_ref;
  png_uint_32 final_width;
  final_width = row_info->width * png_pass_inc[pass];
  switch (row_info->pixel_depth)
  {
    case 1:
    {
      helper_helper_png_do_read_interlace_1_3(row, pass, png_pass_inc, row_info, final_width);
    }

    case 2:
    {
      helper_helper_png_do_read_interlace_1_4(row, pass, png_pass_inc, row_info, final_width);
    }

    case 4:
    {
      helper_helper_png_do_read_interlace_1_2(row, pass, png_pass_inc, row_info, final_width);
    }

    default:
    {
      helper_helper_png_do_read_interlace_1_1(row, pass, png_pass_inc, row_info, final_width);
    }

  }

  row_info->width = final_width;
  row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) final_width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) final_width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  *row_info_ref = row_info;
}


/*** DEPENDENCIES:
void helper_helper_png_do_read_interlace_1_1(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  size_t pixel_bytes = row_info->pixel_depth >> 3;
  png_bytep sp = row + (((size_t) (row_info->width - 1)) * pixel_bytes);
  png_bytep dp = row + (((size_t) (final_width - 1)) * pixel_bytes);
  int jstop = (int) png_pass_inc[pass];
  png_uint_32 i;
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v[8];
    int j;
    memcpy(v, sp, pixel_bytes);
    for (j = 0; j < jstop; j += 1)
    {
      memcpy(dp, v, pixel_bytes);
      dp -= pixel_bytes;
    }

    sp -= pixel_bytes;
  }

  break;
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
typedef unsigned int png_uint_32
----------------------------
void helper_helper_png_do_read_interlace_1_3(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 3));
  png_bytep dp = row + ((size_t) ((final_width - 1) >> 3));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  int jstop = (int) png_pass_inc[pass];
  png_byte v;
  png_uint_32 i;
  int j;
  {
    sshift = 7 - ((row_info->width + 7) & 0x07);
    dshift = 7 - ((final_width + 7) & 0x07);
    s_start = 0;
    s_end = 7;
    s_inc = 1;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    v = (png_byte) (((*sp) >> sshift) & 0x01);
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0x7f7f >> (7 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
}


----------------------------
typedef unsigned char png_byte
----------------------------
void helper_helper_png_do_read_interlace_1_2(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 1));
  png_bytep dp = row + ((size_t) ((final_width - 1) >> 1));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  png_uint_32 i;
  int jstop = (int) png_pass_inc[pass];
  {
    sshift = (1 - ((row_info->width + 1) & 0x01)) << 2;
    dshift = (1 - ((final_width + 1) & 0x01)) << 2;
    s_start = 0;
    s_end = 4;
    s_inc = 4;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v = (png_byte) (((*sp) >> sshift) & 0x0f);
    int j;
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0xf0f >> (4 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
}


----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
void helper_helper_png_do_read_interlace_1_4(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((png_uint_32) ((row_info->width - 1) >> 2));
  png_bytep dp = row + ((png_uint_32) ((final_width - 1) >> 2));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  int jstop = (int) png_pass_inc[pass];
  png_uint_32 i;
  {
    sshift = (3 - ((row_info->width + 3) & 0x03)) << 1;
    dshift = (3 - ((final_width + 3) & 0x03)) << 1;
    s_start = 0;
    s_end = 6;
    s_inc = 2;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v;
    int j;
    v = (png_byte) (((*sp) >> sshift) & 0x03);
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0x3f3f >> (6 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
}


----------------------------
***/


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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
void helper_png_do_read_interlace_1(png_row_infop * const row_info_ref, png_bytep row, int pass, static const unsigned int png_pass_inc[7])
{
  png_row_infop row_info = *row_info_ref;
  png_uint_32 final_width;
  final_width = row_info->width * png_pass_inc[pass];
  switch (row_info->pixel_depth)
  {
    case 1:
    {
      helper_helper_png_do_read_interlace_1_3(row, pass, png_pass_inc, row_info, final_width);
    }

    case 2:
    {
      helper_helper_png_do_read_interlace_1_4(row, pass, png_pass_inc, row_info, final_width);
    }

    case 4:
    {
      helper_helper_png_do_read_interlace_1_2(row, pass, png_pass_inc, row_info, final_width);
    }

    default:
    {
      helper_helper_png_do_read_interlace_1_1(row, pass, png_pass_inc, row_info, final_width);
    }

  }

  row_info->width = final_width;
  row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) final_width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) final_width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  *row_info_ref = row_info;
}


----------------------------
***/


// hint:  ['row_ref is a mutable refrence to png_bytep', 'prev_row_ref is a mutable refrence to png_const_bytep', 'a_ref is a mutable refrence to int', 'c_ref is a mutable refrence to int']
void helper_png_read_filter_row_paeth_1byte_pixel_1(png_bytep * const row_ref, png_const_bytep * const prev_row_ref, int * const a_ref, int * const c_ref)
{
  png_bytep row = *row_ref;
  png_const_bytep prev_row = *prev_row_ref;
  int a = *a_ref;
  int c = *c_ref;
  int b;
  int pa;
  int pb;
  int pc;
  int p;
  a &= 0xff;
  b = *prev_row;
  prev_row += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  if (pb < pa)
  {
    pa = pb;
    a = b;
  }
  if (pc < pa)
  {
    a = c;
  }
  c = b;
  a += *row;
  *row = (png_byte) a;
  row += 1;
  *row_ref = row;
  *prev_row_ref = prev_row;
  *a_ref = a;
  *c_ref = c;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static void png_read_filter_row_paeth_1byte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  png_bytep rp_end = row + row_info->rowbytes;
  int a;
  int c;
  c = *prev_row;
  prev_row += 1;
  a = (*row) + c;
  *row = (png_byte) a;
  row += 1;
  while (row < rp_end)
  {
    helper_png_read_filter_row_paeth_1byte_pixel_1(&row, &prev_row, &a, &c);
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
void helper_png_read_filter_row_paeth_1byte_pixel_1(png_bytep * const row_ref, png_const_bytep * const prev_row_ref, int * const a_ref, int * const c_ref)
{
  png_bytep row = *row_ref;
  png_const_bytep prev_row = *prev_row_ref;
  int a = *a_ref;
  int c = *c_ref;
  int b;
  int pa;
  int pb;
  int pc;
  int p;
  a &= 0xff;
  b = *prev_row;
  prev_row += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  if (pb < pa)
  {
    pa = pb;
    a = b;
  }
  if (pc < pa)
  {
    a = c;
  }
  c = b;
  a += *row;
  *row = (png_byte) a;
  row += 1;
  *row_ref = row;
  *prev_row_ref = prev_row;
  *a_ref = a;
  *c_ref = c;
}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_read_filter_row_sub(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp = row + bpp;
  (void) prev_row;
  for (i = bpp; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*(rp - bpp)))) & 0xff);
    rp += 1;
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
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['row_ref is a mutable refrence to png_bytep', 'prev_row_ref is a mutable refrence to png_const_bytep']
void helper_png_read_filter_row_paeth_multibyte_pixel_1(png_bytep * const row_ref, png_const_bytep * const prev_row_ref, unsigned int bpp)
{
  png_bytep row = *row_ref;
  png_const_bytep prev_row = *prev_row_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  c = *(prev_row - bpp);
  a = *(row - bpp);
  b = *prev_row;
  prev_row += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  if (pb < pa)
  {
    pa = pb;
    a = b;
  }
  if (pc < pa)
  {
    a = c;
  }
  a += *row;
  *row = (png_byte) a;
  row += 1;
  *row_ref = row;
  *prev_row_ref = prev_row;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static void png_read_filter_row_paeth_multibyte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp_end = row + bpp;
  while (row < rp_end)
  {
    int a = (*row) + (*prev_row);
    prev_row += 1;
    *row = (png_byte) a;
    row += 1;
  }

  rp_end = rp_end + (row_info->rowbytes - bpp);
  while (row < rp_end)
  {
    helper_png_read_filter_row_paeth_multibyte_pixel_1(&row, &prev_row, bpp);
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
typedef unsigned char png_byte
----------------------------
void helper_png_read_filter_row_paeth_multibyte_pixel_1(png_bytep * const row_ref, png_const_bytep * const prev_row_ref, unsigned int bpp)
{
  png_bytep row = *row_ref;
  png_const_bytep prev_row = *prev_row_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  c = *(prev_row - bpp);
  a = *(row - bpp);
  b = *prev_row;
  prev_row += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  if (pb < pa)
  {
    pa = pb;
    a = b;
  }
  if (pc < pa)
  {
    a = c;
  }
  a += *row;
  *row = (png_byte) a;
  row += 1;
  *row_ref = row;
  *prev_row_ref = prev_row;
}


----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_read_filter_row_avg(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  size_t istop = row_info->rowbytes - bpp;
  for (i = 0; i < bpp; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) (*pp)) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) ((*pp) + (*(rp - bpp)))) / 2)) & 0xff);
    pp += 1;
    rp += 1;
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
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_read_filter_row_up(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*pp))) & 0xff);
    pp += 1;
    rp += 1;
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
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_init_filter_functions(png_structrp pp)
{
  unsigned int bpp = (pp->pixel_depth + 7) >> 3;
  pp->read_filter[1 - 1] = png_read_filter_row_sub;
  pp->read_filter[2 - 1] = png_read_filter_row_up;
  pp->read_filter[3 - 1] = png_read_filter_row_avg;
  if (bpp == 1)
  {
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_1byte_pixel;
  }
  else
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_multibyte_pixel;
}


/*** DEPENDENCIES:
static void png_read_filter_row_paeth_1byte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  png_bytep rp_end = row + row_info->rowbytes;
  int a;
  int c;
  c = *prev_row;
  prev_row += 1;
  a = (*row) + c;
  *row = (png_byte) a;
  row += 1;
  while (row < rp_end)
  {
    helper_png_read_filter_row_paeth_1byte_pixel_1(&row, &prev_row, &a, &c);
  }

}


----------------------------
static void png_read_filter_row_sub(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp = row + bpp;
  (void) prev_row;
  for (i = bpp; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*(rp - bpp)))) & 0xff);
    rp += 1;
  }

}


----------------------------
static void png_read_filter_row_paeth_multibyte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp_end = row + bpp;
  while (row < rp_end)
  {
    int a = (*row) + (*prev_row);
    prev_row += 1;
    *row = (png_byte) a;
    row += 1;
  }

  rp_end = rp_end + (row_info->rowbytes - bpp);
  while (row < rp_end)
  {
    helper_png_read_filter_row_paeth_multibyte_pixel_1(&row, &prev_row, bpp);
  }

}


----------------------------
static void png_read_filter_row_avg(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  size_t istop = row_info->rowbytes - bpp;
  for (i = 0; i < bpp; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) (*pp)) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) ((*pp) + (*(rp - bpp)))) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void png_read_filter_row_up(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*pp))) & 0xff);
    pp += 1;
    rp += 1;
  }

}


----------------------------
***/


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
typedef png_row_info *png_row_infop
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
static void png_init_filter_functions(png_structrp pp)
{
  unsigned int bpp = (pp->pixel_depth + 7) >> 3;
  pp->read_filter[1 - 1] = png_read_filter_row_sub;
  pp->read_filter[2 - 1] = png_read_filter_row_up;
  pp->read_filter[3 - 1] = png_read_filter_row_avg;
  if (bpp == 1)
  {
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_1byte_pixel;
  }
  else
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_multibyte_pixel;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['dp_ref is a mutable refrence to png_bytep', 'sp_ref is a mutable refrence to png_const_bytep', 'row_width_ref is a mutable refrence to png_alloc_size_t']
void helper_helper_png_combine_row_1_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, int display, unsigned int pass, unsigned int pixel_depth)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  static const png_uint_32 row_mask[2][3][6] = {{{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
  static const png_uint_32 display_mask[2][3][3] = {{{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
  png_uint_32 pixels_per_byte = 8 / pixel_depth;
  png_uint_32 mask;
  mask = (display) ? (display_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass >> 1]) : (row_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass]);
  for (;;)
  {
    png_uint_32 m;
    m = mask;
    mask = (m >> 8) | (m << 24);
    m &= 0xff;
    if (m != 0)
    {
      if (m != 0xff)
      {
        *dp = (png_byte) (((*dp) & (~m)) | ((*sp) & m));
      }
      else
        *dp = *sp;
    }
    if (row_width <= pixels_per_byte)
    {
      break;
    }
    row_width -= pixels_per_byte;
    dp += 1;
    sp += 1;
  }

  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['dp_ref is a mutable refrence to png_bytep', 'sp_ref is a mutable refrence to png_const_bytep', 'row_width_ref is a mutable refrence to png_alloc_size_t']
void helper_helper_helper_helper_png_combine_row_1_2_1_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, unsigned int bytes_to_jump, unsigned int bytes_to_copy)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  if (((((((png_uint_32) ((size_t) ((const void *) dp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0) && ((((png_uint_32) ((size_t) ((const void *) sp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_32))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_32))) == 0))
  {
    png_uint_32p dp32 = (void *) dp;
    png_const_uint_32p sp32 = (const void *) sp;
    size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_32));
    do
    {
      size_t c = bytes_to_copy;
      do
      {
        *dp32 = *sp32;
        sp32 += 1;
        dp32 += 1;
        c -= sizeof(png_uint_32);
      }
      while (c > 0);
      if (row_width <= bytes_to_jump)
      {
        return;
      }
      dp32 += skip;
      sp32 += skip;
      row_width -= bytes_to_jump;
    }
    while (bytes_to_copy <= row_width);
    dp = (png_bytep) dp32;
    sp = (png_const_bytep) sp32;
    do
    {
      *dp = *sp;
      sp += 1;
      dp += 1;
    }
    while ((--row_width) > 0);
    return;
  }
  else
  {
    png_uint_16p dp16 = (void *) dp;
    png_const_uint_16p sp16 = (const void *) sp;
    size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_16));
    do
    {
      size_t c = bytes_to_copy;
      do
      {
        *dp16 = *sp16;
        sp16 += 1;
        dp16 += 1;
        c -= sizeof(png_uint_16);
      }
      while (c > 0);
      if (row_width <= bytes_to_jump)
      {
        return;
      }
      dp16 += skip;
      sp16 += skip;
      row_width -= bytes_to_jump;
    }
    while (bytes_to_copy <= row_width);
    dp = (png_bytep) dp16;
    sp = (png_const_bytep) sp16;
    do
    {
      *dp = *sp;
      sp += 1;
      dp += 1;
    }
    while ((--row_width) > 0);
    return;
  }
  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef const png_uint_16 *png_const_uint_16p
----------------------------
typedef png_uint_16 *png_uint_16p
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef unsigned short png_uint_16
----------------------------
typedef const png_uint_32 *png_const_uint_32p
----------------------------
typedef png_uint_32 *png_uint_32p
----------------------------
***/


// hint:  ['dp_ref is a mutable refrence to png_bytep', 'sp_ref is a mutable refrence to png_const_bytep', 'row_width_ref is a mutable refrence to png_alloc_size_t', 'bytes_to_copy_ref is a mutable refrence to unsigned int']
void helper_helper_helper_png_combine_row_1_2_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, unsigned int * const bytes_to_copy_ref, unsigned int bytes_to_jump)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  unsigned int bytes_to_copy = *bytes_to_copy_ref;
  if (((((bytes_to_copy < 16) && ((((png_uint_16) ((size_t) ((const void *) dp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((((png_uint_16) ((size_t) ((const void *) sp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_16))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_16))) == 0))
  {
    helper_helper_helper_helper_png_combine_row_1_2_1_1(&dp, &sp, &row_width, bytes_to_jump, bytes_to_copy);
  }
  for (;;)
  {
    memcpy(dp, sp, bytes_to_copy);
    if (row_width <= bytes_to_jump)
    {
      return;
    }
    sp += bytes_to_jump;
    dp += bytes_to_jump;
    row_width -= bytes_to_jump;
    if (bytes_to_copy > row_width)
    {
      bytes_to_copy = (unsigned int) row_width;
    }
  }

  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
  *bytes_to_copy_ref = bytes_to_copy;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef size_t png_alloc_size_t
----------------------------
void helper_helper_helper_helper_png_combine_row_1_2_1_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, unsigned int bytes_to_jump, unsigned int bytes_to_copy)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  if (((((((png_uint_32) ((size_t) ((const void *) dp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0) && ((((png_uint_32) ((size_t) ((const void *) sp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_32))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_32))) == 0))
  {
    png_uint_32p dp32 = (void *) dp;
    png_const_uint_32p sp32 = (const void *) sp;
    size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_32));
    do
    {
      size_t c = bytes_to_copy;
      do
      {
        *dp32 = *sp32;
        sp32 += 1;
        dp32 += 1;
        c -= sizeof(png_uint_32);
      }
      while (c > 0);
      if (row_width <= bytes_to_jump)
      {
        return;
      }
      dp32 += skip;
      sp32 += skip;
      row_width -= bytes_to_jump;
    }
    while (bytes_to_copy <= row_width);
    dp = (png_bytep) dp32;
    sp = (png_const_bytep) sp32;
    do
    {
      *dp = *sp;
      sp += 1;
      dp += 1;
    }
    while ((--row_width) > 0);
    return;
  }
  else
  {
    png_uint_16p dp16 = (void *) dp;
    png_const_uint_16p sp16 = (const void *) sp;
    size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_16));
    do
    {
      size_t c = bytes_to_copy;
      do
      {
        *dp16 = *sp16;
        sp16 += 1;
        dp16 += 1;
        c -= sizeof(png_uint_16);
      }
      while (c > 0);
      if (row_width <= bytes_to_jump)
      {
        return;
      }
      dp16 += skip;
      sp16 += skip;
      row_width -= bytes_to_jump;
    }
    while (bytes_to_copy <= row_width);
    dp = (png_bytep) dp16;
    sp = (png_const_bytep) sp16;
    do
    {
      *dp = *sp;
      sp += 1;
      dp += 1;
    }
    while ((--row_width) > 0);
    return;
  }
  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['dp_ref is a mutable refrence to png_bytep', 'pixel_depth_ref is a mutable refrence to unsigned int', 'sp_ref is a mutable refrence to png_const_bytep', 'row_width_ref is a mutable refrence to png_alloc_size_t']
void helper_helper_png_combine_row_1_2(png_bytep * const dp_ref, unsigned int * const pixel_depth_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, png_const_structrp png_ptr, int display, unsigned int pass)
{
  png_bytep dp = *dp_ref;
  unsigned int pixel_depth = *pixel_depth_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  unsigned int bytes_to_copy;
  unsigned int bytes_to_jump;
  if (pixel_depth & 7)
  {
    png_error(png_ptr, "invalid user transform pixel depth");
  }
  pixel_depth >>= 3;
  row_width *= pixel_depth;
  {
    unsigned int offset = (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7) * pixel_depth;
    row_width -= offset;
    dp += offset;
    sp += offset;
  }
  if (display != 0)
  {
    bytes_to_copy = (1 << ((6 - pass) >> 1)) * pixel_depth;
    if (bytes_to_copy > row_width)
    {
      bytes_to_copy = (unsigned int) row_width;
    }
  }
  else
    bytes_to_copy = pixel_depth;
  bytes_to_jump = (1 << ((7 - pass) >> 1)) * pixel_depth;
  switch (bytes_to_copy)
  {
    case 1:
    {
      for (;;)
      {
        *dp = *sp;
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        dp += bytes_to_jump;
        sp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }

    }

    case 2:
    {
      do
      {
        dp[0] = sp[0];
        dp[1] = sp[1];
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        sp += bytes_to_jump;
        dp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }
      while (row_width > 1);
      *dp = *sp;
      return;
    }

    case 3:
    {
      for (;;)
      {
        dp[0] = sp[0];
        dp[1] = sp[1];
        dp[2] = sp[2];
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        sp += bytes_to_jump;
        dp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }

    }

    default:
    {
      helper_helper_helper_png_combine_row_1_2_1(&dp, &sp, &row_width, &bytes_to_copy, bytes_to_jump);
    }

  }

  *dp_ref = dp;
  *pixel_depth_ref = pixel_depth;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef size_t png_alloc_size_t
----------------------------
void helper_helper_helper_png_combine_row_1_2_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, unsigned int * const bytes_to_copy_ref, unsigned int bytes_to_jump)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  unsigned int bytes_to_copy = *bytes_to_copy_ref;
  if (((((bytes_to_copy < 16) && ((((png_uint_16) ((size_t) ((const void *) dp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((((png_uint_16) ((size_t) ((const void *) sp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_16))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_16))) == 0))
  {
    helper_helper_helper_helper_png_combine_row_1_2_1_1(&dp, &sp, &row_width, bytes_to_jump, bytes_to_copy);
  }
  for (;;)
  {
    memcpy(dp, sp, bytes_to_copy);
    if (row_width <= bytes_to_jump)
    {
      return;
    }
    sp += bytes_to_jump;
    dp += bytes_to_jump;
    row_width -= bytes_to_jump;
    if (bytes_to_copy > row_width)
    {
      bytes_to_copy = (unsigned int) row_width;
    }
  }

  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
  *bytes_to_copy_ref = bytes_to_copy;
}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef const png_struct *png_const_structrp
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


// hint:  ['dp_ref is a mutable refrence to png_bytep', 'pixel_depth_ref is a mutable refrence to unsigned int', 'sp_ref is a mutable refrence to png_const_bytep', 'row_width_ref is a mutable refrence to png_alloc_size_t']
void helper_png_combine_row_1(png_bytep * const dp_ref, unsigned int * const pixel_depth_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, png_const_structrp png_ptr, int display, unsigned int pass)
{
  png_bytep dp = *dp_ref;
  unsigned int pixel_depth = *pixel_depth_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  if (row_width <= (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))
  {
    return;
  }
  if (pixel_depth < 8)
  {
    helper_helper_png_combine_row_1_1(&dp, &sp, &row_width, display, pass, pixel_depth);
  }
  else
  {
    helper_helper_png_combine_row_1_2(&dp, &pixel_depth, &sp, &row_width, png_ptr, display, pass);
  }
  *dp_ref = dp;
  *pixel_depth_ref = pixel_depth;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned char png_byte
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
void helper_helper_png_combine_row_1_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, int display, unsigned int pass, unsigned int pixel_depth)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  static const png_uint_32 row_mask[2][3][6] = {{{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
  static const png_uint_32 display_mask[2][3][3] = {{{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
  png_uint_32 pixels_per_byte = 8 / pixel_depth;
  png_uint_32 mask;
  mask = (display) ? (display_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass >> 1]) : (row_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass]);
  for (;;)
  {
    png_uint_32 m;
    m = mask;
    mask = (m >> 8) | (m << 24);
    m &= 0xff;
    if (m != 0)
    {
      if (m != 0xff)
      {
        *dp = (png_byte) (((*dp) & (~m)) | ((*sp) & m));
      }
      else
        *dp = *sp;
    }
    if (row_width <= pixels_per_byte)
    {
      break;
    }
    row_width -= pixels_per_byte;
    dp += 1;
    sp += 1;
  }

  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


----------------------------
void helper_helper_png_combine_row_1_2(png_bytep * const dp_ref, unsigned int * const pixel_depth_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, png_const_structrp png_ptr, int display, unsigned int pass)
{
  png_bytep dp = *dp_ref;
  unsigned int pixel_depth = *pixel_depth_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  unsigned int bytes_to_copy;
  unsigned int bytes_to_jump;
  if (pixel_depth & 7)
  {
    png_error(png_ptr, "invalid user transform pixel depth");
  }
  pixel_depth >>= 3;
  row_width *= pixel_depth;
  {
    unsigned int offset = (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7) * pixel_depth;
    row_width -= offset;
    dp += offset;
    sp += offset;
  }
  if (display != 0)
  {
    bytes_to_copy = (1 << ((6 - pass) >> 1)) * pixel_depth;
    if (bytes_to_copy > row_width)
    {
      bytes_to_copy = (unsigned int) row_width;
    }
  }
  else
    bytes_to_copy = pixel_depth;
  bytes_to_jump = (1 << ((7 - pass) >> 1)) * pixel_depth;
  switch (bytes_to_copy)
  {
    case 1:
    {
      for (;;)
      {
        *dp = *sp;
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        dp += bytes_to_jump;
        sp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }

    }

    case 2:
    {
      do
      {
        dp[0] = sp[0];
        dp[1] = sp[1];
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        sp += bytes_to_jump;
        dp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }
      while (row_width > 1);
      *dp = *sp;
      return;
    }

    case 3:
    {
      for (;;)
      {
        dp[0] = sp[0];
        dp[1] = sp[1];
        dp[2] = sp[2];
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        sp += bytes_to_jump;
        dp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }

    }

    default:
    {
      helper_helper_helper_png_combine_row_1_2_1(&dp, &sp, &row_width, &bytes_to_copy, bytes_to_jump);
    }

  }

  *dp_ref = dp;
  *pixel_depth_ref = pixel_depth;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


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


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned char png_byte
----------------------------
void helper_png_combine_row_1(png_bytep * const dp_ref, unsigned int * const pixel_depth_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, png_const_structrp png_ptr, int display, unsigned int pass)
{
  png_bytep dp = *dp_ref;
  unsigned int pixel_depth = *pixel_depth_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  if (row_width <= (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))
  {
    return;
  }
  if (pixel_depth < 8)
  {
    helper_helper_png_combine_row_1_1(&dp, &sp, &row_width, display, pass, pixel_depth);
  }
  else
  {
    helper_helper_png_combine_row_1_2(&dp, &pixel_depth, &sp, &row_width, png_ptr, display, pass);
  }
  *dp_ref = dp;
  *pixel_depth_ref = pixel_depth;
  *sp_ref = sp;
  *row_width_ref = row_width;
}


----------------------------
typedef const png_struct *png_const_structrp
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


/*** DEPENDENCIES:
typedef unsigned char png_byte
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


