// hint:  ['rowsize_ref is a mutable refrence to png_uint_32', 'palnum_ref is a mutable refrence to unsigned int', 'bit_depth_ref is a mutable refrence to int', 'color_type_ref is a mutable refrence to int']
void helper_pngx_read_bmp_2(png_uint_32 * const rowsize_ref, unsigned int * const palnum_ref, int * const bit_depth_ref, int * const color_type_ref, png_uint_32 width, unsigned int pixdepth, png_uint_32 rgba_mask[4])
{
  png_uint_32 rowsize = *rowsize_ref;
  unsigned int palnum = *palnum_ref;
  int bit_depth = *bit_depth_ref;
  int color_type = *color_type_ref;
  palnum = 0;
  bit_depth = 8;
  switch (pixdepth)
  {
    case 16:
    {
      rowsize = ((width * 2) + 3) & (~3);
      break;
    }

    case 24:
    {
      rowsize = ((width * 3) + 3) & (~3);
      break;
    }

    case 32:
    {
      rowsize = width * 4;
      break;
    }

    default:
    {
      bit_depth = 0;
      rowsize = 0;
    }

  }

  if ((rowsize / width) < (pixdepth / 8))
  {
    rowsize = 0;
  }
  color_type = (rgba_mask[3] != 0) ? (2 | 4) : (2);
  *rowsize_ref = rowsize;
  *palnum_ref = palnum;
  *bit_depth_ref = bit_depth;
  *color_type_ref = color_type;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
***/


static unsigned int bmp_get_word(png_bytep ptr)
{
  return ((unsigned int) ptr[0]) + (((unsigned int) ptr[1]) << 8);
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static void bmp_memset_bytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  memset(ptr + offset, ch, len);
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static void bmp_memset_halfbytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  if (len == 0)
  {
    return;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    *ptr = (png_byte) (((*ptr) & 0xf0) | (ch & 0x0f));
    ch = ((ch & 0xf0) >> 4) | ((ch & 0x0f) << 4);
    ptr += 1;
    len -= 1;
  }
  memset(ptr, ch, len / 2);
  if (len & 1)
  {
    ptr[len / 2] = (png_byte) (ch & 0xf0);
  }
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static size_t bmp_fread_bytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  result = fread(ptr + offset, 1, len, stream);
  if (len & 1)
  {
    getc(stream);
  }
  return result;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static size_t bmp_fread_halfbytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  int ch;
  if (len == 0)
  {
    return 0;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    for (result = 0; result < (len - 1); result += 2)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      *ptr = (png_byte) (((*ptr) & 0xf0) | ((ch & 0xf0) >> 4));
      ptr += 1;
      *ptr = (png_byte) ((ch & 0x0f) << 4);
    }

  }
  else
  {
    result = fread(ptr, 1, (len + 1) / 2, stream) * 2;
  }
  if (len & 2)
  {
    getc(stream);
  }
  return (result <= len) ? (result) : (len);
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static void bmp_process_mask(png_uint_32 bmp_mask, png_bytep sig_bit, png_bytep shift_bit)
{
  *sig_bit = (*shift_bit = (png_byte) 0);
  if (bmp_mask == 0)
  {
    return;
  }
  while ((bmp_mask & 1) == 0)
  {
    bmp_mask >>= 1;
    *shift_bit += 1;
  }

  while (bmp_mask != 0)
  {
    if (((bmp_mask & 1) == 0) || ((*sig_bit) >= 8))
    {
      *sig_bit = (png_byte) 0;
      return;
    }
    bmp_mask >>= 1;
    *sig_bit += 1;
  }

}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
***/


static void bmp_to_png_rows(png_bytepp row_pointers, png_uint_32 width, png_uint_32 height, unsigned int pixdepth, png_bytep rgba_sig, png_bytep rgba_shift)
{
  png_bytep src_ptr;
  png_bytep dest_ptr;
  unsigned int rgba_mask[4];
  unsigned int num_samples;
  unsigned int sample;
  unsigned int mask;
  unsigned int wpix;
  png_uint_32 dwpix;
  png_uint_32 x;
  png_uint_32 y;
  unsigned int i;
  if (pixdepth == 24)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y];
      for (x = 0; x < width; x += 1, src_ptr += 3)
      {
        png_byte tmp = src_ptr[0];
        src_ptr[0] = src_ptr[2];
        src_ptr[2] = tmp;
      }

    }

    return;
  }
  num_samples = (rgba_sig[3] != 0) ? (4) : (3);
  for (i = 0; i < num_samples; i += 1)
  {
    rgba_mask[i] = (1U << rgba_sig[i]) - 1;
  }

  if (pixdepth == 16)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y] + ((width - 1) * 2);
      dest_ptr = row_pointers[y] + ((width - 1) * num_samples);
      for (x = 0; x < width; x += 1, src_ptr -= 2, dest_ptr -= num_samples)
      {
        wpix = ((unsigned int) src_ptr[0]) + (((unsigned int) src_ptr[1]) << 8);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (wpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
  else
    if (pixdepth == 32)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = (dest_ptr = row_pointers[y]);
      for (x = 0; x < width; x += 1, src_ptr += 4, dest_ptr += num_samples)
      {
        dwpix = ((((png_uint_32) src_ptr[0]) + (((png_uint_32) src_ptr[1]) << 8)) + (((png_uint_32) src_ptr[2]) << 16)) + (((png_uint_32) src_ptr[3]) << 24);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (dwpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
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


// hint:  ['compression_ref is a mutable refrence to png_uint_32']
void helper_pngx_read_bmp_3(png_uint_32 * const compression_ref, png_structp png_ptr, const png_bytep bih, png_uint_32 bihsize, unsigned int pixdepth, png_uint_32 rgba_mask[4])
{
  png_uint_32 compression = *compression_ref;
  if (compression == 0)
  {
    if (pixdepth == 16)
    {
      compression = 3;
      rgba_mask[0] = 0x7c00;
      rgba_mask[1] = 0x03e0;
      rgba_mask[2] = 0x001f;
    }
    else
    {
      rgba_mask[0] = (png_uint_32) 0x00ff0000L;
      rgba_mask[1] = (png_uint_32) 0x0000ff00L;
      rgba_mask[2] = (png_uint_32) 0x000000ffL;
    }
  }
  else
    if (compression == 3)
  {
    if (bihsize >= (40 + 12))
    {
      rgba_mask[0] = bmp_get_dword(bih + 40);
      rgba_mask[1] = bmp_get_dword(bih + 44);
      rgba_mask[2] = bmp_get_dword(bih + 48);
    }
    else
      png_error(png_ptr, "Missing color mask in BMP file");
  }
  if (bihsize >= (40 + 16))
  {
    rgba_mask[3] = bmp_get_dword(bih + 52);
  }
  *compression_ref = compression;
}


/*** DEPENDENCIES:
static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
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
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'crt_row_ref is a mutable refrence to png_bytepp', 'crtn_ref is a mutable refrence to size_t', 'dcrtn_ref is a mutable refrence to size_t', 'b1_ref is a mutable refrence to unsigned int', 'b2_ref is a mutable refrence to unsigned int', 'ch_ref is a mutable refrence to int']
void helper_helper_helper_helper_bmp_read_rows_1_1_1_2(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  ch = getc(stream);
  b1 = (unsigned int) ch;
  ch = getc(stream);
  b2 = (unsigned int) ch;
  if (ch == EOF)
  {
    break;
  }
  dcrtn = (b1 < (endn - crtn)) ? (crtn + b1) : (endn);
  for (; b2 > 0; b2 -= 1)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crt_row += inc;
    crtn = 0;
    result += 1;
    if (crt_row == end_row)
    {
      break;
    }
  }

  if (crt_row != end_row)
  {
    bmp_memset_fn(*crt_row, crtn, 0, dcrtn - crtn);
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'crt_row_ref is a mutable refrence to png_bytepp', 'crtn_ref is a mutable refrence to size_t', 'ch_ref is a mutable refrence to int']
void helper_helper_helper_helper_bmp_read_rows_1_1_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, int * const ch_ref, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  int ch = *ch_ref;
  bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
  crt_row += inc;
  crtn = 0;
  result += 1;
  if (crt_row == end_row)
  {
    ch = getc(stream);
    if ((ch != EOF) && (ch != 0))
    {
      ungetc(ch, stream);
      break;
    }
    getc(stream);
    break;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *ch_ref = ch;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'crt_row_ref is a mutable refrence to png_bytepp', 'crtn_ref is a mutable refrence to size_t', 'dcrtn_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to unsigned int', 'b1_ref is a mutable refrence to unsigned int', 'b2_ref is a mutable refrence to unsigned int', 'ch_ref is a mutable refrence to int']
void helper_helper_helper_bmp_read_rows_1_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  if (b2 == 0)
  {
    helper_helper_helper_helper_bmp_read_rows_1_1_1_1(&result, &crt_row, &crtn, &ch, end_row, stream, inc, endn);
  }
  else
    if (b2 == 1)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crt_row += inc;
    crtn = 0;
    result = (begin_row <= end_row) ? (end_row - begin_row) : (begin_row - end_row);
    break;
  }
  else
    if (b2 == 2)
  {
    helper_helper_helper_helper_bmp_read_rows_1_1_1_2(&result, &crt_row, &crtn, &dcrtn, &b1, &b2, &ch, end_row, stream, inc, endn);
  }
  else
  {
    len = (b2 <= (endn - crtn)) ? (b2) : ((unsigned int) (endn - crtn));
    if (bmp_fread_fn(*crt_row, crtn, len, stream) != len)
    {
      break;
    }
    crtn += len;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
void helper_helper_helper_helper_bmp_read_rows_1_1_1_2(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  ch = getc(stream);
  b1 = (unsigned int) ch;
  ch = getc(stream);
  b2 = (unsigned int) ch;
  if (ch == EOF)
  {
    break;
  }
  dcrtn = (b1 < (endn - crtn)) ? (crtn + b1) : (endn);
  for (; b2 > 0; b2 -= 1)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crt_row += inc;
    crtn = 0;
    result += 1;
    if (crt_row == end_row)
    {
      break;
    }
  }

  if (crt_row != end_row)
  {
    bmp_memset_fn(*crt_row, crtn, 0, dcrtn - crtn);
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
void helper_helper_helper_helper_bmp_read_rows_1_1_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, int * const ch_ref, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  int ch = *ch_ref;
  bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
  crt_row += inc;
  crtn = 0;
  result += 1;
  if (crt_row == end_row)
  {
    ch = getc(stream);
    if ((ch != EOF) && (ch != 0))
    {
      ungetc(ch, stream);
      break;
    }
    getc(stream);
    break;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *ch_ref = ch;
}


----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'crt_row_ref is a mutable refrence to png_bytepp', 'crtn_ref is a mutable refrence to size_t', 'dcrtn_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to unsigned int', 'b1_ref is a mutable refrence to unsigned int', 'b2_ref is a mutable refrence to unsigned int', 'ch_ref is a mutable refrence to int']
void helper_helper_bmp_read_rows_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  ch = getc(stream);
  b1 = (unsigned int) ch;
  ch = getc(stream);
  b2 = (unsigned int) ch;
  if (ch == EOF)
  {
    break;
  }
  if (b1 == 0)
  {
    helper_helper_helper_bmp_read_rows_1_1_1(&result, &crt_row, &crtn, &dcrtn, &len, &b1, &b2, &ch, begin_row, end_row, stream, inc, endn);
  }
  else
  {
    len = (b1 <= (endn - crtn)) ? (b1) : ((unsigned int) (endn - crtn));
    bmp_memset_fn(*crt_row, crtn, (int) b2, len);
    crtn += len;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
void helper_helper_helper_bmp_read_rows_1_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  if (b2 == 0)
  {
    helper_helper_helper_helper_bmp_read_rows_1_1_1_1(&result, &crt_row, &crtn, &ch, end_row, stream, inc, endn);
  }
  else
    if (b2 == 1)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crt_row += inc;
    crtn = 0;
    result = (begin_row <= end_row) ? (end_row - begin_row) : (begin_row - end_row);
    break;
  }
  else
    if (b2 == 2)
  {
    helper_helper_helper_helper_bmp_read_rows_1_1_1_2(&result, &crt_row, &crtn, &dcrtn, &b1, &b2, &ch, end_row, stream, inc, endn);
  }
  else
  {
    len = (b2 <= (endn - crtn)) ? (b2) : ((unsigned int) (endn - crtn));
    if (bmp_fread_fn(*crt_row, crtn, len, stream) != len)
    {
      break;
    }
    crtn += len;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'crt_row_ref is a mutable refrence to png_bytepp', 'crtn_ref is a mutable refrence to size_t', 'dcrtn_ref is a mutable refrence to size_t', 'endn_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to unsigned int', 'b1_ref is a mutable refrence to unsigned int', 'b2_ref is a mutable refrence to unsigned int', 'ch_ref is a mutable refrence to int']
size_t helper_bmp_read_rows_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, size_t * const endn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE * const stream, int inc)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  size_t endn = *endn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  if (compression == 1)
  {
    endn = row_size;
  }
  else
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
  }
  for (crt_row = begin_row; crt_row != end_row;)
  {
    helper_helper_bmp_read_rows_1_1(&result, &crt_row, &crtn, &dcrtn, &len, &b1, &b2, &ch, begin_row, end_row, stream, inc, endn);
  }

  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *endn_ref = endn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
void helper_helper_bmp_read_rows_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  ch = getc(stream);
  b1 = (unsigned int) ch;
  ch = getc(stream);
  b2 = (unsigned int) ch;
  if (ch == EOF)
  {
    break;
  }
  if (b1 == 0)
  {
    helper_helper_helper_bmp_read_rows_1_1_1(&result, &crt_row, &crtn, &dcrtn, &len, &b1, &b2, &ch, begin_row, end_row, stream, inc, endn);
  }
  else
  {
    len = (b1 <= (endn - crtn)) ? (b1) : ((unsigned int) (endn - crtn));
    bmp_memset_fn(*crt_row, crtn, (int) b2, len);
    crtn += len;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


static size_t bmp_read_rows(png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE *stream)
{
  size_t result;
  png_bytepp crt_row;
  int inc;
  size_t crtn;
  size_t dcrtn;
  size_t endn;
  unsigned int len;
  unsigned int b1;
  unsigned int b2;
  int ch;
  void (*bmp_memset_fn)(png_bytep, size_t, int, size_t);
  unsigned int bmp_memset_fn_idx = 0;
  size_t (*bmp_fread_fn)(png_bytep, size_t, size_t, FILE *);
  unsigned int bmp_fread_fn_idx = 0;
  if (row_size == 0)
  {
    return 0;
  }
  inc = (begin_row <= end_row) ? (1) : (-1);
  crtn = 0;
  result = 0;
  if (compression == 2)
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
    bmp_memset_fn_idx = bmp_memset_halfbytes;
    bmp_fread_fn_idx = bmp_fread_halfbytes;
  }
  else
  {
    endn = row_size;
    bmp_memset_fn_idx = bmp_memset_bytes;
    bmp_fread_fn_idx = bmp_fread_bytes;
  }
  if ((compression == 0) || (compression == 3))
  {
    for (crt_row = begin_row; crt_row != end_row; crt_row += inc)
    {
      crtn = bmp_fread_fn(*crt_row, 0, endn, stream);
      if (crtn != endn)
      {
        break;
      }
      result += 1;
    }

  }
  else
    if ((compression == 1) || (compression == 2))
  {
    helper_bmp_read_rows_1(&result, &crt_row, &crtn, &dcrtn, &endn, &len, &b1, &b2, &ch, begin_row, end_row, row_size, compression, stream, inc);
  }
  else
    return 0;
  for (; crt_row != end_row; crt_row += inc)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crtn = 0;
  }

  return result;
}


/*** DEPENDENCIES:
size_t helper_bmp_read_rows_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, size_t * const endn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE * const stream, int inc)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  size_t endn = *endn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  if (compression == 1)
  {
    endn = row_size;
  }
  else
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
  }
  for (crt_row = begin_row; crt_row != end_row;)
  {
    helper_helper_bmp_read_rows_1_1(&result, &crt_row, &crtn, &dcrtn, &len, &b1, &b2, &ch, begin_row, end_row, stream, inc, endn);
  }

  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *endn_ref = endn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}


----------------------------
static void bmp_memset_bytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  memset(ptr + offset, ch, len);
}


----------------------------
static void bmp_memset_halfbytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  if (len == 0)
  {
    return;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    *ptr = (png_byte) (((*ptr) & 0xf0) | (ch & 0x0f));
    ch = ((ch & 0xf0) >> 4) | ((ch & 0x0f) << 4);
    ptr += 1;
    len -= 1;
  }
  memset(ptr, ch, len / 2);
  if (len & 1)
  {
    ptr[len / 2] = (png_byte) (ch & 0xf0);
  }
}


----------------------------
typedef unsigned char png_byte
----------------------------
static size_t bmp_fread_halfbytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  int ch;
  if (len == 0)
  {
    return 0;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    for (result = 0; result < (len - 1); result += 2)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      *ptr = (png_byte) (((*ptr) & 0xf0) | ((ch & 0xf0) >> 4));
      ptr += 1;
      *ptr = (png_byte) ((ch & 0x0f) << 4);
    }

  }
  else
  {
    result = fread(ptr, 1, (len + 1) / 2, stream) * 2;
  }
  if (len & 2)
  {
    getc(stream);
  }
  return (result <= len) ? (result) : (len);
}


----------------------------
typedef png_byte **png_bytepp
----------------------------
static size_t bmp_fread_bytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  result = fread(ptr + offset, 1, len, stream);
  if (len & 1)
  {
    getc(stream);
  }
  return result;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['bihsize_ref is a mutable refrence to png_uint_32', 'skip_ref is a mutable refrence to png_uint_32', 'width_ref is a mutable refrence to png_uint_32', 'height_ref is a mutable refrence to png_uint_32', 'topdown_ref is a mutable refrence to int', 'pixdepth_ref is a mutable refrence to unsigned int', 'compression_ref is a mutable refrence to png_uint_32', 'palsize_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to unsigned int']
int helper_pngx_read_bmp_1(png_uint_32 * const bihsize_ref, png_uint_32 * const skip_ref, png_uint_32 * const width_ref, png_uint_32 * const height_ref, int * const topdown_ref, unsigned int * const pixdepth_ref, png_uint_32 * const compression_ref, unsigned int * const palsize_ref, unsigned int * const i_ref, FILE * const stream, const png_bytep bih)
{
  png_uint_32 bihsize = *bihsize_ref;
  png_uint_32 skip = *skip_ref;
  png_uint_32 width = *width_ref;
  png_uint_32 height = *height_ref;
  int topdown = *topdown_ref;
  unsigned int pixdepth = *pixdepth_ref;
  png_uint_32 compression = *compression_ref;
  unsigned int palsize = *palsize_ref;
  unsigned int i = *i_ref;
  width = bmp_get_dword(bih + 4);
  height = bmp_get_dword(bih + 8);
  pixdepth = bmp_get_word(bih + 14);
  compression = bmp_get_dword(bih + 16);
  palsize = 4;
  if (height > ((png_uint_32) 0x7fffffffL))
  {
    height = (((png_uint_32) (-1)) - height) + 1;
    topdown = 1;
  }
  if ((bihsize == 40) && (compression == 3))
  {
    i = (skip <= 16) ? ((unsigned int) skip) : (16);
    if (fread(bih + 40, i, 1, stream) != 1)
    {
      return 0;
    }
    bihsize += i;
    skip -= i;
  }
  *bihsize_ref = bihsize;
  *skip_ref = skip;
  *width_ref = width;
  *height_ref = height;
  *topdown_ref = topdown;
  *pixdepth_ref = pixdepth;
  *compression_ref = compression;
  *palsize_ref = palsize;
  *i_ref = i;
}


/*** DEPENDENCIES:
static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}


----------------------------
static unsigned int bmp_get_word(png_bytep ptr)
{
  return ((unsigned int) ptr[0]) + (((unsigned int) ptr[1]) << 8);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  png_byte bfh[14 + 124];
  const png_bytep bih = bfh + 14;
  png_byte rgbq[4];
  png_uint_32 offbits;
  png_uint_32 bihsize;
  png_uint_32 skip;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowsize;
  int topdown;
  unsigned int pixdepth;
  png_uint_32 compression;
  unsigned int palsize;
  unsigned int palnum;
  png_uint_32 rgba_mask[4];
  png_byte rgba_sig[4];
  png_byte rgba_shift[4];
  int bit_depth;
  int color_type;
  png_color palette[256];
  png_color_8 sig_bit;
  png_bytepp row_pointers;
  png_bytepp begin_row;
  png_bytepp end_row;
  unsigned int i;
  size_t y;
  for (i = 0;; i += 1)
  {
    if (fread(bfh, 14 + 4, 1, stream) != 1)
    {
      i += 1;
    }
    else
      if (bmp_get_word(bfh + 0) == 0x4d42)
    {
      break;
    }
    if (fread(bfh, (128 - 14) - 4, 1, stream) != 1)
    {
      i += 1;
    }
    if (i > 0)
    {
      return 0;
    }
  }

  offbits = bmp_get_dword(bfh + 10);
  bihsize = bmp_get_dword(bfh + 14);
  if ((((offbits > ((png_uint_32) 0x7fffffffL)) || (bihsize > ((png_uint_32) 0x7fffffffL))) || (offbits < (bihsize + 14))) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (bihsize > 124)
  {
    skip = bihsize - 124;
    bihsize = 124;
  }
  else
    skip = 0;
  if (fread(bih + 4, bihsize - 4, 1, stream) != 1)
  {
    return 0;
  }
  if (skip > 0)
  {
    if (fseek(stream, (long) skip, 1) != 0)
    {
      return 0;
    }
  }
  skip = (offbits - bihsize) - 14;
  topdown = 0;
  if (bihsize < 40)
  {
    width = bmp_get_word(bih + 4);
    height = bmp_get_word(bih + 6);
    pixdepth = bmp_get_word(bih + 10);
    compression = 0;
    palsize = 3;
  }
  else
  {
    helper_pngx_read_bmp_1(&bihsize, &skip, &width, &height, &topdown, &pixdepth, &compression, &palsize, &i, stream, bih);
  }
  memset(rgba_mask, 0, sizeof(rgba_mask));
  if (pixdepth > 8)
  {
    helper_pngx_read_bmp_3(&compression, png_ptr, bih, bihsize, pixdepth, rgba_mask);
  }
  switch (compression)
  {
    case 0:
    {
      if (((pixdepth > 0) && ((32 % pixdepth) != 0)) && (pixdepth != 24))
      {
        pixdepth = 0;
      }
      break;
    }

    case 1:
    {
      if (pixdepth != 8)
      {
        pixdepth = 0;
      }
      break;
    }

    case 2:
    {
      if (pixdepth != 4)
      {
        pixdepth = 0;
      }
      break;
    }

    case 3:
    {
      if ((pixdepth != 16) && (pixdepth != 32))
      {
        pixdepth = 0;
      }
      break;
    }

    case 4:
    {
      png_error(png_ptr, "JPEG-compressed BMP files are not supported");
      break;
    }

    case 5:
    {
      if (ungetc(getc(stream), stream) == 0)
      {
        png_set_sig_bytes(png_ptr, 8);
      }
      png_set_read_fn(png_ptr, stream, 0);
      png_read_png(png_ptr, info_ptr, 0, 0);
      return 1;
    }

    default:
    {
      png_error(png_ptr, "Unsupported compression method in BMP file");
    }

  }

  if (((width == 0) || (width > ((png_uint_32) 0x7fffffffL))) || (height == 0))
  {
    png_error(png_ptr, "Invalid image dimensions in BMP file");
  }
  if (pixdepth == 0)
  {
    png_error(png_ptr, "Invalid pixel depth in BMP file");
  }
  if (pixdepth <= 8)
  {
    palnum = skip / palsize;
    if (palnum > 256)
    {
      palnum = 256;
    }
    skip -= palsize * palnum;
    rowsize = (((width + (32 / pixdepth)) - 1) / (32 / pixdepth)) * 4;
    bit_depth = pixdepth;
    color_type = (palnum > 0) ? (2 | 1) : (0);
  }
  else
  {
    helper_pngx_read_bmp_2(&rowsize, &palnum, &bit_depth, &color_type, width, pixdepth, rgba_mask);
  }
  if (rowsize == 0)
  {
    png_error(png_ptr, "Can't handle exceedingly large BMP dimensions");
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, 0, 0, 0);
  if (pixdepth > 8)
  {
    for (i = 0; i < 4; i += 1)
    {
      bmp_process_mask(rgba_mask[i], &rgba_sig[i], &rgba_shift[i]);
    }

    if (((rgba_sig[0] == 0) || (rgba_sig[1] == 0)) || (rgba_sig[2] == 0))
    {
      png_error(png_ptr, "Invalid color mask in BMP file");
    }
    if ((((rgba_sig[0] != 8) || (rgba_sig[1] != 8)) || (rgba_sig[2] != 8)) || ((rgba_sig[3] != 0) && (rgba_sig[3] != 8)))
    {
      sig_bit.red = rgba_sig[0];
      sig_bit.green = rgba_sig[1];
      sig_bit.blue = rgba_sig[2];
      sig_bit.alpha = rgba_sig[3];
      png_set_sBIT(png_ptr, info_ptr, &sig_bit);
    }
  }
  if (palnum > 0)
  {
    for (i = 0; i < palnum; i += 1)
    {
      if (fread(rgbq, palsize, 1, stream) != 1)
      {
        break;
      }
      palette[i].red = rgbq[2];
      palette[i].green = rgbq[1];
      palette[i].blue = rgbq[0];
    }

    png_set_PLTE(png_ptr, info_ptr, palette, i);
    if (i != palnum)
    {
      png_error(png_ptr, "Error reading color palette in BMP file");
    }
  }
  row_pointers = pngx_malloc_rows_extended(png_ptr, info_ptr, rowsize, -1);
  if (topdown)
  {
    begin_row = row_pointers;
    end_row = row_pointers + height;
  }
  else
  {
    begin_row = (row_pointers + height) - 1;
    end_row = row_pointers - 1;
  }
  if (skip > 0)
  {
    fseek(stream, (long) skip, 1);
  }
  y = bmp_read_rows(begin_row, end_row, rowsize, compression, stream);
  if (pixdepth > 8)
  {
    bmp_to_png_rows(row_pointers, width, height, pixdepth, rgba_sig, rgba_shift);
  }
  if (y != ((size_t) height))
  {
    png_error(png_ptr, "Error reading BMP file");
  }
  return 1;
}


/*** DEPENDENCIES:
static unsigned int bmp_get_word(png_bytep ptr)
{
  return ((unsigned int) ptr[0]) + (((unsigned int) ptr[1]) << 8);
}


----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
void png_read_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, voidp params)
{
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  png_read_info(png_ptr, info_ptr);
  if (info_ptr->height > (((png_uint_32) (-1)) / (sizeof(png_bytep))))
  {
    png_error(png_ptr, "Image is too high to process with png_read_png()");
  }
  if ((transforms & 0x8000) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SCALE_16 not supported");
  }
  if ((transforms & 0x0001) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_STRIP_16 not supported");
  }
  if ((transforms & 0x0002) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_STRIP_ALPHA not supported");
  }
  if ((transforms & 0x0004) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKING not supported");
  }
  if ((transforms & 0x0008) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKSWAP not supported");
  }
  if ((transforms & 0x0010) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_EXPAND not supported");
  }
  if ((transforms & 0x0020) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_MONO not supported");
  }
  if ((transforms & 0x0040) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SHIFT not supported");
  }
  if ((transforms & 0x0080) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_BGR not supported");
  }
  if ((transforms & 0x0100) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ALPHA not supported");
  }
  if ((transforms & 0x0200) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ENDIAN not supported");
  }
  if ((transforms & 0x0400) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_ALPHA not supported");
  }
  if ((transforms & 0x2000) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_GRAY_TO_RGB not supported");
  }
  if ((transforms & 0x4000) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_EXPAND_16 not supported");
  }
  (void) png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);
  png_free_data(png_ptr, info_ptr, 0x0040U, 0);
  if (info_ptr->row_pointers == 0)
  {
    png_uint_32 iptr;
    info_ptr->row_pointers = png_malloc(png_ptr, info_ptr->height * (sizeof(png_bytep)));
    for (iptr = 0; iptr < info_ptr->height; iptr += 1)
    {
      info_ptr->row_pointers[iptr] = 0;
    }

    info_ptr->free_me |= 0x0040U;
    for (iptr = 0; iptr < info_ptr->height; iptr += 1)
    {
      info_ptr->row_pointers[iptr] = png_malloc(png_ptr, info_ptr->rowbytes);
    }

  }
  png_read_image(png_ptr, info_ptr->row_pointers);
  info_ptr->valid |= 0x8000U;
  png_read_end(png_ptr, info_ptr);
  (void) params;
}


----------------------------
static void bmp_process_mask(png_uint_32 bmp_mask, png_bytep sig_bit, png_bytep shift_bit)
{
  *sig_bit = (*shift_bit = (png_byte) 0);
  if (bmp_mask == 0)
  {
    return;
  }
  while ((bmp_mask & 1) == 0)
  {
    bmp_mask >>= 1;
    *shift_bit += 1;
  }

  while (bmp_mask != 0)
  {
    if (((bmp_mask & 1) == 0) || ((*sig_bit) >= 8))
    {
      *sig_bit = (png_byte) 0;
      return;
    }
    bmp_mask >>= 1;
    *sig_bit += 1;
  }

}


----------------------------
typedef png_byte **png_bytepp
----------------------------
void helper_pngx_read_bmp_2(png_uint_32 * const rowsize_ref, unsigned int * const palnum_ref, int * const bit_depth_ref, int * const color_type_ref, png_uint_32 width, unsigned int pixdepth, png_uint_32 rgba_mask[4])
{
  png_uint_32 rowsize = *rowsize_ref;
  unsigned int palnum = *palnum_ref;
  int bit_depth = *bit_depth_ref;
  int color_type = *color_type_ref;
  palnum = 0;
  bit_depth = 8;
  switch (pixdepth)
  {
    case 16:
    {
      rowsize = ((width * 2) + 3) & (~3);
      break;
    }

    case 24:
    {
      rowsize = ((width * 3) + 3) & (~3);
      break;
    }

    case 32:
    {
      rowsize = width * 4;
      break;
    }

    default:
    {
      bit_depth = 0;
      rowsize = 0;
    }

  }

  if ((rowsize / width) < (pixdepth / 8))
  {
    rowsize = 0;
  }
  color_type = (rgba_mask[3] != 0) ? (2 | 4) : (2);
  *rowsize_ref = rowsize;
  *palnum_ref = palnum;
  *bit_depth_ref = bit_depth;
  *color_type_ref = color_type;
}


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
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
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
static void bmp_to_png_rows(png_bytepp row_pointers, png_uint_32 width, png_uint_32 height, unsigned int pixdepth, png_bytep rgba_sig, png_bytep rgba_shift)
{
  png_bytep src_ptr;
  png_bytep dest_ptr;
  unsigned int rgba_mask[4];
  unsigned int num_samples;
  unsigned int sample;
  unsigned int mask;
  unsigned int wpix;
  png_uint_32 dwpix;
  png_uint_32 x;
  png_uint_32 y;
  unsigned int i;
  if (pixdepth == 24)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y];
      for (x = 0; x < width; x += 1, src_ptr += 3)
      {
        png_byte tmp = src_ptr[0];
        src_ptr[0] = src_ptr[2];
        src_ptr[2] = tmp;
      }

    }

    return;
  }
  num_samples = (rgba_sig[3] != 0) ? (4) : (3);
  for (i = 0; i < num_samples; i += 1)
  {
    rgba_mask[i] = (1U << rgba_sig[i]) - 1;
  }

  if (pixdepth == 16)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y] + ((width - 1) * 2);
      dest_ptr = row_pointers[y] + ((width - 1) * num_samples);
      for (x = 0; x < width; x += 1, src_ptr -= 2, dest_ptr -= num_samples)
      {
        wpix = ((unsigned int) src_ptr[0]) + (((unsigned int) src_ptr[1]) << 8);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (wpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
  else
    if (pixdepth == 32)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = (dest_ptr = row_pointers[y]);
      for (x = 0; x < width; x += 1, src_ptr += 4, dest_ptr += num_samples)
      {
        dwpix = ((((png_uint_32) src_ptr[0]) + (((png_uint_32) src_ptr[1]) << 8)) + (((png_uint_32) src_ptr[2]) << 16)) + (((png_uint_32) src_ptr[3]) << 24);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (dwpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
}


----------------------------
typedef struct png_info_def png_info
----------------------------
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


----------------------------
void helper_pngx_read_bmp_3(png_uint_32 * const compression_ref, png_structp png_ptr, const png_bytep bih, png_uint_32 bihsize, unsigned int pixdepth, png_uint_32 rgba_mask[4])
{
  png_uint_32 compression = *compression_ref;
  if (compression == 0)
  {
    if (pixdepth == 16)
    {
      compression = 3;
      rgba_mask[0] = 0x7c00;
      rgba_mask[1] = 0x03e0;
      rgba_mask[2] = 0x001f;
    }
    else
    {
      rgba_mask[0] = (png_uint_32) 0x00ff0000L;
      rgba_mask[1] = (png_uint_32) 0x0000ff00L;
      rgba_mask[2] = (png_uint_32) 0x000000ffL;
    }
  }
  else
    if (compression == 3)
  {
    if (bihsize >= (40 + 12))
    {
      rgba_mask[0] = bmp_get_dword(bih + 40);
      rgba_mask[1] = bmp_get_dword(bih + 44);
      rgba_mask[2] = bmp_get_dword(bih + 48);
    }
    else
      png_error(png_ptr, "Missing color mask in BMP file");
  }
  if (bihsize >= (40 + 16))
  {
    rgba_mask[3] = bmp_get_dword(bih + 52);
  }
  *compression_ref = compression;
}


----------------------------
static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}


----------------------------
typedef unsigned char png_byte
----------------------------
static size_t bmp_read_rows(png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE *stream)
{
  size_t result;
  png_bytepp crt_row;
  int inc;
  size_t crtn;
  size_t dcrtn;
  size_t endn;
  unsigned int len;
  unsigned int b1;
  unsigned int b2;
  int ch;
  void (*bmp_memset_fn)(png_bytep, size_t, int, size_t);
  unsigned int bmp_memset_fn_idx = 0;
  size_t (*bmp_fread_fn)(png_bytep, size_t, size_t, FILE *);
  unsigned int bmp_fread_fn_idx = 0;
  if (row_size == 0)
  {
    return 0;
  }
  inc = (begin_row <= end_row) ? (1) : (-1);
  crtn = 0;
  result = 0;
  if (compression == 2)
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
    bmp_memset_fn_idx = bmp_memset_halfbytes;
    bmp_fread_fn_idx = bmp_fread_halfbytes;
  }
  else
  {
    endn = row_size;
    bmp_memset_fn_idx = bmp_memset_bytes;
    bmp_fread_fn_idx = bmp_fread_bytes;
  }
  if ((compression == 0) || (compression == 3))
  {
    for (crt_row = begin_row; crt_row != end_row; crt_row += inc)
    {
      crtn = bmp_fread_fn(*crt_row, 0, endn, stream);
      if (crtn != endn)
      {
        break;
      }
      result += 1;
    }

  }
  else
    if ((compression == 1) || (compression == 2))
  {
    helper_bmp_read_rows_1(&result, &crt_row, &crtn, &dcrtn, &endn, &len, &b1, &b2, &ch, begin_row, end_row, row_size, compression, stream, inc);
  }
  else
    return 0;
  for (; crt_row != end_row; crt_row += inc)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crtn = 0;
  }

  return result;
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
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
void png_set_read_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (read_data_fn != 0)
  {
    png_ptr->read_data_fn = read_data_fn;
  }
  else
    png_ptr->read_data_fn = png_default_read_data;
  if (png_ptr->write_data_fn != 0)
  {
    png_ptr->write_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
  png_ptr->output_flush_fn = 0;
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
int helper_pngx_read_bmp_1(png_uint_32 * const bihsize_ref, png_uint_32 * const skip_ref, png_uint_32 * const width_ref, png_uint_32 * const height_ref, int * const topdown_ref, unsigned int * const pixdepth_ref, png_uint_32 * const compression_ref, unsigned int * const palsize_ref, unsigned int * const i_ref, FILE * const stream, const png_bytep bih)
{
  png_uint_32 bihsize = *bihsize_ref;
  png_uint_32 skip = *skip_ref;
  png_uint_32 width = *width_ref;
  png_uint_32 height = *height_ref;
  int topdown = *topdown_ref;
  unsigned int pixdepth = *pixdepth_ref;
  png_uint_32 compression = *compression_ref;
  unsigned int palsize = *palsize_ref;
  unsigned int i = *i_ref;
  width = bmp_get_dword(bih + 4);
  height = bmp_get_dword(bih + 8);
  pixdepth = bmp_get_word(bih + 14);
  compression = bmp_get_dword(bih + 16);
  palsize = 4;
  if (height > ((png_uint_32) 0x7fffffffL))
  {
    height = (((png_uint_32) (-1)) - height) + 1;
    topdown = 1;
  }
  if ((bihsize == 40) && (compression == 3))
  {
    i = (skip <= 16) ? ((unsigned int) skip) : (16);
    if (fread(bih + 40, i, 1, stream) != 1)
    {
      return 0;
    }
    bihsize += i;
    skip -= i;
  }
  *bihsize_ref = bihsize;
  *skip_ref = skip;
  *width_ref = width;
  *height_ref = height;
  *topdown_ref = topdown;
  *pixdepth_ref = pixdepth;
  *compression_ref = compression;
  *palsize_ref = palsize;
  *i_ref = i;
}


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


int pngx_sig_is_bmp(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char bmp_fmt_name[] = "BMP";
  static const char os2bmp_fmt_long_name[] = "OS/2 Bitmap";
  static const char winbmp_fmt_long_name[] = "Windows Bitmap";
  png_uint_32 bihsize;
  if (sig_size < (14 + 4))
  {
    return -1;
  }
  if (bmp_get_word(sig) != 0x4d42)
  {
    return 0;
  }
  bihsize = bmp_get_dword(sig + 14);
  if ((bihsize > ((png_uint_32) 0x7fffffffL)) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = bmp_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    if (bihsize == 12)
    {
      *fmt_long_name_ptr = os2bmp_fmt_long_name;
    }
    else
      *fmt_long_name_ptr = winbmp_fmt_long_name;
  }
  return 1;
}


/*** DEPENDENCIES:
static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}


----------------------------
static unsigned int bmp_get_word(png_bytep ptr)
{
  return ((unsigned int) ptr[0]) + (((unsigned int) ptr[1]) << 8);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef const char *png_const_charp
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef const char **png_const_charpp
----------------------------
***/


