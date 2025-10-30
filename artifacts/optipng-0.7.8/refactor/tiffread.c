#include <limits.h>
#include <minitiff.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiffread.c>

struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
};
void minitiff_init_info(struct minitiff_info *info_ptr);
void minitiff_validate_info(const struct minitiff_info *info_ptr);
void minitiff_destroy_info(struct minitiff_info *info_ptr);
void minitiff_read_info(struct minitiff_info *info_ptr, FILE *stream);
void minitiff_read_row(struct minitiff_info *info_ptr, unsigned char *row_ptr, size_t row_index, FILE *stream);
void minitiff_write_info(const struct minitiff_info *info_ptr, FILE *stream);
void minitiff_write_row(const struct minitiff_info *info_ptr, const unsigned char *row_ptr, size_t row_index, FILE *stream);
void minitiff_error(const struct minitiff_info *info_ptr, const char *msg);
void minitiff_warning(const struct minitiff_info *info_ptr, const char *msg);
enum 
{
  MINITIFF_TYPE_NONE = 0x0000,
  MINITIFF_TYPE_BYTE = 0x0001,
  MINITIFF_TYPE_ASCII = 0x0002,
  MINITIFF_TYPE_SHORT = 0x0003,
  MINITIFF_TYPE_LONG = 0x0004,
  MINITIFF_TYPE_RATIONAL = 0x0005,
  MINITIFF_TYPE_SBYTE = 0x0006,
  MINITIFF_TYPE_UNDEFINED = 0x0007,
  MINITIFF_TYPE_SSHORT = 0x0008,
  MINITIFF_TYPE_SLONG = 0x0009,
  MINITIFF_TYPE_SRATIONAL = 0x000a,
  MINITIFF_TYPE_FLOAT = 0x000b,
  MINITIFF_TYPE_DOUBLE = 0x000c,
  MINITIFF_TYPE_IFD = 0x000d,
  MINITIFF_TYPE_LONG64 = 0x0010,
  MINITIFF_TYPE_SLONG64 = 0x0011,
  MINITIFF_TYPE_IFD64 = 0x0012
};
enum 
{
  MINITIFF_TAG_SUBFILE_TYPE = 0x00fe,
  MINITIFF_TAG_OLD_SUBFILE_TYPE = 0x00ff,
  MINITIFF_TAG_WIDTH = 0x0100,
  MINITIFF_TAG_HEIGHT = 0x0101,
  MINITIFF_TAG_BITS_PER_SAMPLE = 0x0102,
  MINITIFF_TAG_COMPRESSION = 0x0103,
  MINITIFF_TAG_PHOTOMETRIC = 0x0106,
  MINITIFF_TAG_THRESHOLDING = 0x0107,
  MINITIFF_TAG_CELL_WIDTH = 0x0108,
  MINITIFF_TAG_CELL_LENGTH = 0x0109,
  MINITIFF_TAG_FILL_ORDER = 0x010a,
  MINITIFF_TAG_DOCUMENT_NAME = 0x010d,
  MINITIFF_TAG_IMAGE_DESCRIPTION = 0x010e,
  MINITIFF_TAG_MAKE = 0x010f,
  MINITIFF_TAG_MODEL = 0x0110,
  MINITIFF_TAG_STRIP_OFFSETS = 0x0111,
  MINITIFF_TAG_ORIENTATION = 0x0112,
  MINITIFF_TAG_SAMPLES_PER_PIXEL = 0x0115,
  MINITIFF_TAG_ROWS_PER_STRIP = 0x0116,
  MINITIFF_TAG_STRIP_BYTE_COUNTS = 0x0117,
  MINITIFF_TAG_MIN_SAMPLE_VALUE = 0x0118,
  MINITIFF_TAG_MAX_SAMPLE_VALUE = 0x0119,
  MINITIFF_TAG_X_RESOLUTION = 0x011a,
  MINITIFF_TAG_Y_RESOLUTION = 0x011b,
  MINITIFF_TAG_PLANAR_CONFIGURATION = 0x011c,
  MINITIFF_TAG_PAGE_NAME = 0x011d,
  MINITIFF_TAG_X_POSITION = 0x011e,
  MINITIFF_TAG_Y_POSITION = 0x011f,
  MINITIFF_TAG_RESOLUTION_UNIT = 0x0128,
  MINITIFF_TAG_PAGE_NUMBER = 0x0129,
  MINITIFF_TAG_TRANSFER_FUNCTION = 0x012d,
  MINITIFF_TAG_SOFTWARE = 0x0131,
  MINITIFF_TAG_DATE_TIME = 0x0132,
  MINITIFF_TAG_ARTIST = 0x013b,
  MINITIFF_TAG_HOST_COMPUTER = 0x013c,
  MINITIFF_TAG_PREDICTOR = 0x013d,
  MINITIFF_TAG_WHITE_POINT = 0x013e,
  MINITIFF_TAG_PRIMARY_CHROMATICITIES = 0x013f,
  MINITIFF_TAG_COLOR_MAP = 0x0140,
  MINITIFF_TAG_HALFTONE_HINTS = 0x0141,
  MINITIFF_TAG_TILE_WIDTH = 0x0142,
  MINITIFF_TAG_TILE_LENGTH = 0x0143,
  MINITIFF_TAG_TILE_OFFSETS = 0x0144,
  MINITIFF_TAG_BYTE_COUNTS = 0x0145,
  MINITIFF_TAG_XMP = 0x02bc,
  MINITIFF_TAG_COPYRIGHT = 0x8298,
  MINITIFF_TAG_IPTC = 0x83bb,
  MINITIFF_TAG_EXIF_IFD = 0x8769,
  MINITIFF_TAG_ICC_PROFILE = 0x8773,
  MINITIFF_TAG_GPS_IFD = 0x8825,
  MINITIFF_TAG_INTEROPERABILITY_IFD = 0xa005,
  MINITIFF_TAG_PRINT_IM = 0xc4a5
};
enum 
{
  MINITIFF_COMPRESSION_NONE = 0x0001,
  MINITIFF_COMPRESSION_CCITT_RLE = 0x0002,
  MINITIFF_COMPRESSION_CCITT_T4 = 0x0003,
  MINITIFF_COMPRESSION_CCITT_FAX3 = 0x0003,
  MINITIFF_COMPRESSION_CCITT_T6 = 0x0004,
  MINITIFF_COMPRESSION_CCITT_FAX4 = 0x0004,
  MINITIFF_COMPRESSION_LZW = 0x0005,
  MINITIFF_COMPRESSION_OLD_JPEG = 0x0006,
  MINITIFF_COMPRESSION_JPEG = 0x0007,
  MINITIFF_COMPRESSION_ADOBE_DEFLATE = 0x0008,
  MINITIFF_COMPRESSION_ITU_T85 = 0x0009,
  MINITIFF_COMPRESSION_ITU_T43 = 0x000a,
  MINITIFF_COMPRESSION_NEXT_RLE = 0x7ffe,
  MINITIFF_COMPRESSION_CCITT_RLEW = 0x8003,
  MINITIFF_COMPRESSION_PACKBITS = 0x8005,
  MINITIFF_COMPRESSION_THUNDERSCAN = 0x8029,
  MINITIFF_COMPRESSION_IT8_CT_MP = 0x807f,
  MINITIFF_COMPRESSION_IT8_LW = 0x8080,
  MINITIFF_COMPRESSION_IT8_HC = 0x8081,
  MINITIFF_COMPRESSION_IT8_BL = 0x8082,
  MINITIFF_COMPRESSION_PIXARFILM = 0x808c,
  MINITIFF_COMPRESSION_PIXARLOG = 0x808d,
  MINITIFF_COMPRESSION_DEFLATE = 0x80b2,
  MINITIFF_COMPRESSION_KODAK_DCS = 0x80b3,
  MINITIFF_COMPRESSION_JBIG = 0x8765,
  MINITIFF_COMPRESSION_SGI_LOGLUV = 0x8774,
  MINITIFF_COMPRESSION_SGI_LOGLUV24 = 0x8775,
  MINITIFF_COMPRESSION_JPEG2000 = 0x8798,
  MINITIFF_COMPRESSION_LZMA2 = 0x886d
};
enum 
{
  MINITIFF_PHOTOMETRIC_MINWHITE = 0x0000,
  MINITIFF_PHOTOMETRIC_MINBLACK = 0x0001,
  MINITIFF_PHOTOMETRIC_RGB = 0x0002,
  MINITIFF_PHOTOMETRIC_PALETTE = 0x0003,
  MINITIFF_PHOTOMETRIC_MASK = 0x0004,
  MINITIFF_PHOTOMETRIC_SEPARATED = 0x0005,
  MINITIFF_PHOTOMETRIC_YCBCR = 0x0006,
  MINITIFF_PHOTOMETRIC_CIELAB = 0x0008,
  MINITIFF_PHOTOMETRIC_ICCLAB = 0x0009,
  MINITIFF_PHOTOMETRIC_ITULAB = 0x000a,
  MINITIFF_PHOTOMETRIC_CFA = 0x8023,
  MINITIFF_PHOTOMETRIC_LOGL = 0x804c,
  MINITIFF_PHOTOMETRIC_LOGLUV = 0x804d
};
enum 
{
  MINITIFF_ORIENTATION_TOP_LEFT = 0x0001,
  MINITIFF_ORIENTATION_TOP_RIGHT = 0x0002,
  MINITIFF_ORIENTATION_BOTTOM_RIGHT = 0x0003,
  MINITIFF_ORIENTATION_BOTTOM_LEFT = 0x0004,
  MINITIFF_ORIENTATION_LEFT_TOP = 0x0005,
  MINITIFF_ORIENTATION_RIGHT_TOP = 0x0006,
  MINITIFF_ORIENTATION_RIGHT_BOTTOM = 0x0007,
  MINITIFF_ORIENTATION_LEFT_BOTTOM = 0x0008
};
extern const char minitiff_sig_m[4];
extern const char minitiff_sig_i[4];
extern const char minitiff_sig_bigm[4];
extern const char minitiff_sig_bigi[4];
static const char *msg_err_alloc = "Error allocating memory for TIFF file";
static const char *msg_err_read = "Error reading TIFF file";
static const char *msg_err_seek = "Error repositioning TIFF file";
static const char *msg_err_notiff = "Not a TIFF file";
static const char *msg_err_bigtiff = "Unsupported BigTIFF file";
static const char *msg_err_invalid = "Invalid TIFF file";
static const char *msg_err_range = "Value out of the supported range in TIFF file";
static const char *msg_err_unsupported = "Unsupported data in TIFF file";
static const char *msg_warn_metadata = "Unrecognized metadata in TIFF file";
static const char *msg_warn_multiple = "Selected first image from multi-image TIFF file";
struct minitiff_getter
{
  unsigned int (*get_ushort)(const unsigned char *buf_ptr);
  unsigned long (*get_ulong)(const unsigned char *buf_ptr);
};
static unsigned int get_ushort_m(const unsigned char *buf_ptr)
{
  return (((unsigned int) buf_ptr[0]) << 8) + ((unsigned int) buf_ptr[1]);
}

static unsigned int get_ushort_i(const unsigned char *buf_ptr)
{
  return ((unsigned int) buf_ptr[0]) + (((unsigned int) buf_ptr[1]) << 8);
}

static unsigned long get_ulong_m(const unsigned char *buf_ptr)
{
  return (((((unsigned long) buf_ptr[0]) << 24) + (((unsigned long) buf_ptr[1]) << 16)) + (((unsigned long) buf_ptr[2]) << 8)) + ((unsigned long) buf_ptr[3]);
}

static unsigned long get_ulong_i(const unsigned char *buf_ptr)
{
  return ((((unsigned long) buf_ptr[0]) + (((unsigned long) buf_ptr[1]) << 8)) + (((unsigned long) buf_ptr[2]) << 16)) + (((unsigned long) buf_ptr[3]) << 24);
}

static unsigned long get_ulong_value(const struct minitiff_getter *getter_ptr, int tag_type, const unsigned char *buf_ptr)
{
  switch (tag_type)
  {
    case MINITIFF_TYPE_BYTE:
    {
      return (unsigned long) buf_ptr[0];
    }

    case MINITIFF_TYPE_SHORT:
    {
      return (unsigned long) getter_ptr->get_ushort(buf_ptr);
    }

    case MINITIFF_TYPE_LONG:
    {
      return getter_ptr->get_ulong(buf_ptr);
    }

    default:
    {
      return (unsigned long) (-1L);
    }

  }

}

static unsigned long *alloc_ulong_array(struct minitiff_info *info_ptr, size_t count)
{
  unsigned long *result;
  unsigned int result_idx = 0;
  if (count > (((size_t) (-1)) / (sizeof(unsigned long))))
  {
    minitiff_error(info_ptr, msg_err_range);
  }
  result_idx = (unsigned long *) malloc(count * (sizeof(unsigned long)));
  if ((&result[result_idx]) == 0)
  {
    minitiff_error(info_ptr, msg_err_alloc);
  }
  return result;
}

static size_t read_ulong_values(const struct minitiff_getter *getter_ptr, int tag_type, unsigned long values[], size_t count, FILE *stream)
{
  unsigned char buf[4];
  size_t value_size;
  size_t i;
  switch (tag_type)
  {
    case MINITIFF_TYPE_BYTE:
    {
      value_size = 1;
      break;
    }

    case MINITIFF_TYPE_SHORT:
    {
      value_size = 2;
      break;
    }

    case MINITIFF_TYPE_LONG:
    {
      value_size = 4;
      break;
    }

    default:
    {
      return 0;
    }

  }

  for (i = 0; i < count; i += 1)
  {
    if (fread(buf, value_size, 1, stream) != 1)
    {
      break;
    }
    values[i] = get_ulong_value(getter_ptr, tag_type, buf);
  }

  return i;
}

static void seek_to_offset(struct minitiff_info *info_ptr, long offset, FILE *stream)
{
  if (offset < 0)
  {
    minitiff_error(info_ptr, msg_err_range);
  }
  if (ftell(stream) == offset)
  {
    return;
  }
  if (fseek(stream, offset, 0) != 0)
  {
    minitiff_error(info_ptr, msg_err_seek);
  }
}

void minitiff_read_info(struct minitiff_info *info_ptr, FILE *stream)
{
  struct minitiff_getter getter;
  unsigned char buf[12];
  unsigned char *vbuf = buf + 8;
  unsigned long ulvals[4];
  unsigned long ulval;
  long dir_offset;
  unsigned int dir_size;
  unsigned int i;
  unsigned int tag_id;
  unsigned int tag_type;
  size_t count;
  size_t bits_per_sample_count;
  unsigned int bits_per_sample_tag_type;
  unsigned int strip_offsets_tag_type;
  long bits_per_sample_offset;
  long strip_offsets_offset;
  int unknown_metadata_found;
  if (fread(buf, 8, 1, stream) != 1)
  {
    goto err_read;
  }
  if (memcmp(buf, minitiff_sig_m, 4) == 0)
  {
    info_ptr->byte_order = 'M';
    getter.get_ushort = get_ushort_m;
    getter.get_ulong = get_ulong_m;
  }
  else
    if (memcmp(buf, minitiff_sig_i, 4) == 0)
  {
    info_ptr->byte_order = 'I';
    getter.get_ushort = get_ushort_i;
    getter.get_ulong = get_ulong_i;
  }
  else
    if ((memcmp(buf, minitiff_sig_bigm, 4) == 0) || (memcmp(buf, minitiff_sig_bigi, 4) == 0))
  {
    minitiff_error(info_ptr, msg_err_bigtiff);
    return;
  }
  else
  {
    minitiff_error(info_ptr, msg_err_notiff);
    return;
  }
  bits_per_sample_count = 0;
  bits_per_sample_tag_type = (strip_offsets_tag_type = 0);
  bits_per_sample_offset = (strip_offsets_offset = 0);
  dir_offset = (long) getter.get_ulong(buf + 4);
  if ((dir_offset >= 0) && (dir_offset < 8))
  {
    goto err_invalid;
  }
  seek_to_offset(info_ptr, dir_offset, stream);
  if (fread(buf, 2, 1, stream) != 1)
  {
    goto err_read;
  }
  dir_size = getter.get_ushort(buf);
  unknown_metadata_found = 0;
  for (i = 0; i < dir_size; i += 1)
  {
    helper_minitiff_read_info_2(&ulval, &tag_id, &tag_type, &count, &bits_per_sample_count, &bits_per_sample_tag_type, &strip_offsets_tag_type, &bits_per_sample_offset, &strip_offsets_offset, &unknown_metadata_found, info_ptr, stream, getter, buf, vbuf);
  }

  if (fread(buf, 4, 1, stream) != 1)
  {
    goto err_read;
  }
  if (getter.get_ulong(buf) != 0)
  {
    minitiff_warning(info_ptr, msg_warn_multiple);
  }
  if (bits_per_sample_offset != 0)
  {
    helper_minitiff_read_info_1(&count, info_ptr, stream, getter, ulvals, bits_per_sample_count, bits_per_sample_tag_type, bits_per_sample_offset);
  }
  if (strip_offsets_offset != 0)
  {
    count = info_ptr->strip_offsets_count;
    if ((count == 0) || (count > info_ptr->height))
    {
      goto err_invalid;
    }
    if (info_ptr->strip_offsets != 0)
    {
      goto err_invalid;
    }
    info_ptr->strip_offsets = alloc_ulong_array(info_ptr, count);
    seek_to_offset(info_ptr, strip_offsets_offset, stream);
    if (read_ulong_values(&getter, strip_offsets_tag_type, info_ptr->strip_offsets, count, stream) != count)
    {
      goto err_read;
    }
  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}

void minitiff_read_row(struct minitiff_info *info_ptr, unsigned char *row_ptr, size_t row_index, FILE *stream)
{
  size_t row_size;
  size_t strip_index;
  unsigned int bytes_per_sample;
  unsigned int sample_max;
  long offset;
  size_t i;
  bytes_per_sample = (info_ptr->bits_per_sample + 7) / 8;
  row_size = (info_ptr->width * info_ptr->samples_per_pixel) * bytes_per_sample;
  strip_index = row_index / info_ptr->rows_per_strip;
  if (strip_index >= info_ptr->strip_offsets_count)
  {
    goto err_invalid;
  }
  if (((long) info_ptr->strip_offsets[strip_index]) < 0)
  {
    goto err_range;
  }
  offset = (long) (info_ptr->strip_offsets[strip_index] + (row_size * (row_index % info_ptr->rows_per_strip)));
  seek_to_offset(info_ptr, offset, stream);
  if (fread(row_ptr, row_size, 1, stream) != 1)
  {
    goto err_read;
  }
  if (info_ptr->photometric == 0)
  {
    if (bytes_per_sample > 1)
    {
      goto err_unsupported;
    }
    sample_max = (1 << info_ptr->bits_per_sample) - 1;
    for (i = 0; i < row_size; i += 1)
    {
      row_ptr[i] = (unsigned char) (sample_max - row_ptr[i]);
    }

  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_range:
  minitiff_error(info_ptr, msg_err_range);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}


struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
};
void minitiff_init_info(struct minitiff_info *info_ptr);
void minitiff_validate_info(const struct minitiff_info *info_ptr);
void minitiff_destroy_info(struct minitiff_info *info_ptr);
void minitiff_read_info(struct minitiff_info *info_ptr, FILE *stream);
void minitiff_read_row(struct minitiff_info *info_ptr, unsigned char *row_ptr, size_t row_index, FILE *stream);
void minitiff_write_info(const struct minitiff_info *info_ptr, FILE *stream);
void minitiff_write_row(const struct minitiff_info *info_ptr, const unsigned char *row_ptr, size_t row_index, FILE *stream);
void minitiff_error(const struct minitiff_info *info_ptr, const char *msg);
void minitiff_warning(const struct minitiff_info *info_ptr, const char *msg);
enum 
{
  MINITIFF_TYPE_NONE = 0x0000,
  MINITIFF_TYPE_BYTE = 0x0001,
  MINITIFF_TYPE_ASCII = 0x0002,
  MINITIFF_TYPE_SHORT = 0x0003,
  MINITIFF_TYPE_LONG = 0x0004,
  MINITIFF_TYPE_RATIONAL = 0x0005,
  MINITIFF_TYPE_SBYTE = 0x0006,
  MINITIFF_TYPE_UNDEFINED = 0x0007,
  MINITIFF_TYPE_SSHORT = 0x0008,
  MINITIFF_TYPE_SLONG = 0x0009,
  MINITIFF_TYPE_SRATIONAL = 0x000a,
  MINITIFF_TYPE_FLOAT = 0x000b,
  MINITIFF_TYPE_DOUBLE = 0x000c,
  MINITIFF_TYPE_IFD = 0x000d,
  MINITIFF_TYPE_LONG64 = 0x0010,
  MINITIFF_TYPE_SLONG64 = 0x0011,
  MINITIFF_TYPE_IFD64 = 0x0012
};
enum 
{
  MINITIFF_TAG_SUBFILE_TYPE = 0x00fe,
  MINITIFF_TAG_OLD_SUBFILE_TYPE = 0x00ff,
  MINITIFF_TAG_WIDTH = 0x0100,
  MINITIFF_TAG_HEIGHT = 0x0101,
  MINITIFF_TAG_BITS_PER_SAMPLE = 0x0102,
  MINITIFF_TAG_COMPRESSION = 0x0103,
  MINITIFF_TAG_PHOTOMETRIC = 0x0106,
  MINITIFF_TAG_THRESHOLDING = 0x0107,
  MINITIFF_TAG_CELL_WIDTH = 0x0108,
  MINITIFF_TAG_CELL_LENGTH = 0x0109,
  MINITIFF_TAG_FILL_ORDER = 0x010a,
  MINITIFF_TAG_DOCUMENT_NAME = 0x010d,
  MINITIFF_TAG_IMAGE_DESCRIPTION = 0x010e,
  MINITIFF_TAG_MAKE = 0x010f,
  MINITIFF_TAG_MODEL = 0x0110,
  MINITIFF_TAG_STRIP_OFFSETS = 0x0111,
  MINITIFF_TAG_ORIENTATION = 0x0112,
  MINITIFF_TAG_SAMPLES_PER_PIXEL = 0x0115,
  MINITIFF_TAG_ROWS_PER_STRIP = 0x0116,
  MINITIFF_TAG_STRIP_BYTE_COUNTS = 0x0117,
  MINITIFF_TAG_MIN_SAMPLE_VALUE = 0x0118,
  MINITIFF_TAG_MAX_SAMPLE_VALUE = 0x0119,
  MINITIFF_TAG_X_RESOLUTION = 0x011a,
  MINITIFF_TAG_Y_RESOLUTION = 0x011b,
  MINITIFF_TAG_PLANAR_CONFIGURATION = 0x011c,
  MINITIFF_TAG_PAGE_NAME = 0x011d,
  MINITIFF_TAG_X_POSITION = 0x011e,
  MINITIFF_TAG_Y_POSITION = 0x011f,
  MINITIFF_TAG_RESOLUTION_UNIT = 0x0128,
  MINITIFF_TAG_PAGE_NUMBER = 0x0129,
  MINITIFF_TAG_TRANSFER_FUNCTION = 0x012d,
  MINITIFF_TAG_SOFTWARE = 0x0131,
  MINITIFF_TAG_DATE_TIME = 0x0132,
  MINITIFF_TAG_ARTIST = 0x013b,
  MINITIFF_TAG_HOST_COMPUTER = 0x013c,
  MINITIFF_TAG_PREDICTOR = 0x013d,
  MINITIFF_TAG_WHITE_POINT = 0x013e,
  MINITIFF_TAG_PRIMARY_CHROMATICITIES = 0x013f,
  MINITIFF_TAG_COLOR_MAP = 0x0140,
  MINITIFF_TAG_HALFTONE_HINTS = 0x0141,
  MINITIFF_TAG_TILE_WIDTH = 0x0142,
  MINITIFF_TAG_TILE_LENGTH = 0x0143,
  MINITIFF_TAG_TILE_OFFSETS = 0x0144,
  MINITIFF_TAG_BYTE_COUNTS = 0x0145,
  MINITIFF_TAG_XMP = 0x02bc,
  MINITIFF_TAG_COPYRIGHT = 0x8298,
  MINITIFF_TAG_IPTC = 0x83bb,
  MINITIFF_TAG_EXIF_IFD = 0x8769,
  MINITIFF_TAG_ICC_PROFILE = 0x8773,
  MINITIFF_TAG_GPS_IFD = 0x8825,
  MINITIFF_TAG_INTEROPERABILITY_IFD = 0xa005,
  MINITIFF_TAG_PRINT_IM = 0xc4a5
};
enum 
{
  MINITIFF_COMPRESSION_NONE = 0x0001,
  MINITIFF_COMPRESSION_CCITT_RLE = 0x0002,
  MINITIFF_COMPRESSION_CCITT_T4 = 0x0003,
  MINITIFF_COMPRESSION_CCITT_FAX3 = 0x0003,
  MINITIFF_COMPRESSION_CCITT_T6 = 0x0004,
  MINITIFF_COMPRESSION_CCITT_FAX4 = 0x0004,
  MINITIFF_COMPRESSION_LZW = 0x0005,
  MINITIFF_COMPRESSION_OLD_JPEG = 0x0006,
  MINITIFF_COMPRESSION_JPEG = 0x0007,
  MINITIFF_COMPRESSION_ADOBE_DEFLATE = 0x0008,
  MINITIFF_COMPRESSION_ITU_T85 = 0x0009,
  MINITIFF_COMPRESSION_ITU_T43 = 0x000a,
  MINITIFF_COMPRESSION_NEXT_RLE = 0x7ffe,
  MINITIFF_COMPRESSION_CCITT_RLEW = 0x8003,
  MINITIFF_COMPRESSION_PACKBITS = 0x8005,
  MINITIFF_COMPRESSION_THUNDERSCAN = 0x8029,
  MINITIFF_COMPRESSION_IT8_CT_MP = 0x807f,
  MINITIFF_COMPRESSION_IT8_LW = 0x8080,
  MINITIFF_COMPRESSION_IT8_HC = 0x8081,
  MINITIFF_COMPRESSION_IT8_BL = 0x8082,
  MINITIFF_COMPRESSION_PIXARFILM = 0x808c,
  MINITIFF_COMPRESSION_PIXARLOG = 0x808d,
  MINITIFF_COMPRESSION_DEFLATE = 0x80b2,
  MINITIFF_COMPRESSION_KODAK_DCS = 0x80b3,
  MINITIFF_COMPRESSION_JBIG = 0x8765,
  MINITIFF_COMPRESSION_SGI_LOGLUV = 0x8774,
  MINITIFF_COMPRESSION_SGI_LOGLUV24 = 0x8775,
  MINITIFF_COMPRESSION_JPEG2000 = 0x8798,
  MINITIFF_COMPRESSION_LZMA2 = 0x886d
};
enum 
{
  MINITIFF_PHOTOMETRIC_MINWHITE = 0x0000,
  MINITIFF_PHOTOMETRIC_MINBLACK = 0x0001,
  MINITIFF_PHOTOMETRIC_RGB = 0x0002,
  MINITIFF_PHOTOMETRIC_PALETTE = 0x0003,
  MINITIFF_PHOTOMETRIC_MASK = 0x0004,
  MINITIFF_PHOTOMETRIC_SEPARATED = 0x0005,
  MINITIFF_PHOTOMETRIC_YCBCR = 0x0006,
  MINITIFF_PHOTOMETRIC_CIELAB = 0x0008,
  MINITIFF_PHOTOMETRIC_ICCLAB = 0x0009,
  MINITIFF_PHOTOMETRIC_ITULAB = 0x000a,
  MINITIFF_PHOTOMETRIC_CFA = 0x8023,
  MINITIFF_PHOTOMETRIC_LOGL = 0x804c,
  MINITIFF_PHOTOMETRIC_LOGLUV = 0x804d
};
enum 
{
  MINITIFF_ORIENTATION_TOP_LEFT = 0x0001,
  MINITIFF_ORIENTATION_TOP_RIGHT = 0x0002,
  MINITIFF_ORIENTATION_BOTTOM_RIGHT = 0x0003,
  MINITIFF_ORIENTATION_BOTTOM_LEFT = 0x0004,
  MINITIFF_ORIENTATION_LEFT_TOP = 0x0005,
  MINITIFF_ORIENTATION_RIGHT_TOP = 0x0006,
  MINITIFF_ORIENTATION_RIGHT_BOTTOM = 0x0007,
  MINITIFF_ORIENTATION_LEFT_BOTTOM = 0x0008
};
extern const char minitiff_sig_m[4];
extern const char minitiff_sig_i[4];
extern const char minitiff_sig_bigm[4];
extern const char minitiff_sig_bigi[4];
static const char *msg_err_alloc = "Error allocating memory for TIFF file";
static const char *msg_err_read = "Error reading TIFF file";
static const char *msg_err_seek = "Error repositioning TIFF file";
static const char *msg_err_notiff = "Not a TIFF file";
static const char *msg_err_bigtiff = "Unsupported BigTIFF file";
static const char *msg_err_invalid = "Invalid TIFF file";
static const char *msg_err_range = "Value out of the supported range in TIFF file";
static const char *msg_err_unsupported = "Unsupported data in TIFF file";
static const char *msg_warn_metadata = "Unrecognized metadata in TIFF file";
static const char *msg_warn_multiple = "Selected first image from multi-image TIFF file";
struct minitiff_getter
{
  unsigned int (*get_ushort)(const unsigned char *buf_ptr);
  unsigned long (*get_ulong)(const unsigned char *buf_ptr);
};
static unsigned int get_ushort_m(const unsigned char *buf_ptr)
{
  return (((unsigned int) buf_ptr[0]) << 8) + ((unsigned int) buf_ptr[1]);
}

static unsigned int get_ushort_i(const unsigned char *buf_ptr)
{
  return ((unsigned int) buf_ptr[0]) + (((unsigned int) buf_ptr[1]) << 8);
}

static unsigned long get_ulong_m(const unsigned char *buf_ptr)
{
  return (((((unsigned long) buf_ptr[0]) << 24) + (((unsigned long) buf_ptr[1]) << 16)) + (((unsigned long) buf_ptr[2]) << 8)) + ((unsigned long) buf_ptr[3]);
}

static unsigned long get_ulong_i(const unsigned char *buf_ptr)
{
  return ((((unsigned long) buf_ptr[0]) + (((unsigned long) buf_ptr[1]) << 8)) + (((unsigned long) buf_ptr[2]) << 16)) + (((unsigned long) buf_ptr[3]) << 24);
}

static unsigned long get_ulong_value(const struct minitiff_getter *getter_ptr, int tag_type, const unsigned char *buf_ptr)
{
  switch (tag_type)
  {
    case MINITIFF_TYPE_BYTE:
      return (unsigned long) buf_ptr[0];

    case MINITIFF_TYPE_SHORT:
      return (unsigned long) getter_ptr->get_ushort(buf_ptr);

    case MINITIFF_TYPE_LONG:
      return getter_ptr->get_ulong(buf_ptr);

    default:
      return (unsigned long) (-1L);

  }

}

static unsigned long *alloc_ulong_array(struct minitiff_info *info_ptr, size_t count)
{
  unsigned long *result;
  unsigned int result_idx = 0;
  if (count > (((size_t) (-1)) / (sizeof(unsigned long))))
  {
    minitiff_error(info_ptr, msg_err_range);
  }
  result_idx = (unsigned long *) malloc(count * (sizeof(unsigned long)));
  if ((&result[result_idx]) == 0)
  {
    minitiff_error(info_ptr, msg_err_alloc);
  }
  return result;
}

static size_t read_ulong_values(const struct minitiff_getter *getter_ptr, int tag_type, unsigned long values[], size_t count, FILE *stream)
{
  unsigned char buf[4];
  size_t value_size;
  size_t i;
  switch (tag_type)
  {
    case MINITIFF_TYPE_BYTE:
      value_size = 1;
      break;

    case MINITIFF_TYPE_SHORT:
      value_size = 2;
      break;

    case MINITIFF_TYPE_LONG:
      value_size = 4;
      break;

    default:
      return 0;

  }

  for (i = 0; i < count; i += 1)
  {
    if (fread(buf, value_size, 1, stream) != 1)
    {
      break;
    }
    values[i] = get_ulong_value(getter_ptr, tag_type, buf);
  }

  return i;
}

static void seek_to_offset(struct minitiff_info *info_ptr, long offset, FILE *stream)
{
  if (offset < 0)
  {
    minitiff_error(info_ptr, msg_err_range);
  }
  if (ftell(stream) == offset)
  {
    return;
  }
  if (fseek(stream, offset, 0) != 0)
  {
    minitiff_error(info_ptr, msg_err_seek);
  }
}

void minitiff_read_info(struct minitiff_info *info_ptr, FILE *stream)
{
  struct minitiff_getter getter;
  unsigned char buf[12];
  unsigned char *vbuf = buf + 8;
  unsigned long ulvals[4];
  unsigned long ulval;
  long dir_offset;
  unsigned int dir_size;
  unsigned int i;
  unsigned int tag_id;
  unsigned int tag_type;
  size_t count;
  size_t bits_per_sample_count;
  unsigned int bits_per_sample_tag_type;
  unsigned int strip_offsets_tag_type;
  long bits_per_sample_offset;
  long strip_offsets_offset;
  int unknown_metadata_found;
  if (fread(buf, 8, 1, stream) != 1)
  {
    goto err_read;
  }
  if (memcmp(buf, minitiff_sig_m, 4) == 0)
  {
    info_ptr->byte_order = 'M';
    getter.get_ushort = get_ushort_m;
    getter.get_ulong = get_ulong_m;
  }
  else
    if (memcmp(buf, minitiff_sig_i, 4) == 0)
  {
    info_ptr->byte_order = 'I';
    getter.get_ushort = get_ushort_i;
    getter.get_ulong = get_ulong_i;
  }
  else
    if ((memcmp(buf, minitiff_sig_bigm, 4) == 0) || (memcmp(buf, minitiff_sig_bigi, 4) == 0))
  {
    minitiff_error(info_ptr, msg_err_bigtiff);
    return;
  }
  else
  {
    minitiff_error(info_ptr, msg_err_notiff);
    return;
  }
  bits_per_sample_count = 0;
  bits_per_sample_tag_type = (strip_offsets_tag_type = 0);
  bits_per_sample_offset = (strip_offsets_offset = 0);
  dir_offset = (long) getter.get_ulong(buf + 4);
  if ((dir_offset >= 0) && (dir_offset < 8))
  {
    goto err_invalid;
  }
  seek_to_offset(info_ptr, dir_offset, stream);
  if (fread(buf, 2, 1, stream) != 1)
  {
    goto err_read;
  }
  dir_size = getter.get_ushort(buf);
  unknown_metadata_found = 0;
  for (i = 0; i < dir_size; i += 1)
  {
    if (fread(buf, 12, 1, stream) != 1)
    {
      goto err_read;
    }
    tag_id = getter.get_ushort(buf);
    tag_type = getter.get_ushort(buf + 2);
    count = (size_t) getter.get_ulong(buf + 4);
    if (count == 0)
    {
      goto err_unsupported;
    }
    switch (tag_id)
    {
      case MINITIFF_TAG_SUBFILE_TYPE:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        if ((ulval != 0) && (ulval != 1))
      {
        goto err_unsupported;
      }
        break;

      case MINITIFF_TAG_WIDTH:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->width = (size_t) ulval;
        break;

      case MINITIFF_TAG_HEIGHT:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->height = (size_t) ulval;
        break;

      case MINITIFF_TAG_BITS_PER_SAMPLE:
        if (count == 1)
      {
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->bits_per_sample = (unsigned int) ulval;
      }
      else
      {
        bits_per_sample_count = count;
        bits_per_sample_tag_type = tag_type;
        bits_per_sample_offset = (long) getter.get_ulong(vbuf);
      }
        break;

      case MINITIFF_TAG_COMPRESSION:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->compression = (unsigned int) ulval;
        break;

      case MINITIFF_TAG_PHOTOMETRIC:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->photometric = (unsigned int) ulval;
        break;

      case MINITIFF_TAG_STRIP_OFFSETS:
        info_ptr->strip_offsets_count = count;
        if (count == 1)
      {
        if (info_ptr->strip_offsets != 0)
        {
          goto err_invalid;
        }
        info_ptr->strip_offsets = alloc_ulong_array(info_ptr, 1);
        info_ptr->strip_offsets[0] = get_ulong_value(&getter, tag_type, vbuf);
      }
      else
      {
        strip_offsets_tag_type = tag_type;
        strip_offsets_offset = (long) getter.get_ulong(vbuf);
      }
        break;

      case MINITIFF_TAG_ORIENTATION:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->orientation = (unsigned int) ulval;
        break;

      case MINITIFF_TAG_SAMPLES_PER_PIXEL:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->samples_per_pixel = (unsigned int) ulval;
        break;

      case MINITIFF_TAG_ROWS_PER_STRIP:
        if (count != 1)
      {
        goto err_unsupported;
      }
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->rows_per_strip = (size_t) ulval;
        break;

      case MINITIFF_TAG_STRIP_BYTE_COUNTS:
        break;

      case MINITIFF_TAG_PLANAR_CONFIGURATION:

      case MINITIFF_TAG_PREDICTOR:
        if ((count != 1) || (get_ulong_value(&getter, tag_type, vbuf) != 1))
      {
        goto err_unsupported;
      }
        break;

      case MINITIFF_TAG_XMP:

      case MINITIFF_TAG_IPTC:

      case MINITIFF_TAG_EXIF_IFD:

      case MINITIFF_TAG_ICC_PROFILE:

      case MINITIFF_TAG_GPS_IFD:

      case MINITIFF_TAG_INTEROPERABILITY_IFD:

      case MINITIFF_TAG_PRINT_IM:
        if (!unknown_metadata_found)
      {
        unknown_metadata_found = 1;
        minitiff_warning(info_ptr, msg_warn_metadata);
      }
        break;

    }

  }

  if (fread(buf, 4, 1, stream) != 1)
  {
    goto err_read;
  }
  if (getter.get_ulong(buf) != 0)
  {
    minitiff_warning(info_ptr, msg_warn_multiple);
  }
  if (bits_per_sample_offset != 0)
  {
    count = bits_per_sample_count;
    if (count != info_ptr->samples_per_pixel)
    {
      goto err_invalid;
    }
    if (count > 4)
    {
      goto err_unsupported;
    }
    seek_to_offset(info_ptr, bits_per_sample_offset, stream);
    if (read_ulong_values(&getter, bits_per_sample_tag_type, ulvals, count, stream) != count)
    {
      goto err_read;
    }
    while ((--count) > 0)
    {
      if (ulvals[0] != ulvals[count])
      {
        goto err_unsupported;
      }
    }

    info_ptr->bits_per_sample = (unsigned int) ulvals[0];
  }
  if (strip_offsets_offset != 0)
  {
    count = info_ptr->strip_offsets_count;
    if ((count == 0) || (count > info_ptr->height))
    {
      goto err_invalid;
    }
    if (info_ptr->strip_offsets != 0)
    {
      goto err_invalid;
    }
    info_ptr->strip_offsets = alloc_ulong_array(info_ptr, count);
    seek_to_offset(info_ptr, strip_offsets_offset, stream);
    if (read_ulong_values(&getter, strip_offsets_tag_type, info_ptr->strip_offsets, count, stream) != count)
    {
      goto err_read;
    }
  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}

void minitiff_read_row(struct minitiff_info *info_ptr, unsigned char *row_ptr, size_t row_index, FILE *stream)
{
  size_t row_size;
  size_t strip_index;
  unsigned int bytes_per_sample;
  unsigned int sample_max;
  long offset;
  size_t i;
  bytes_per_sample = (info_ptr->bits_per_sample + 7) / 8;
  row_size = (info_ptr->width * info_ptr->samples_per_pixel) * bytes_per_sample;
  strip_index = row_index / info_ptr->rows_per_strip;
  if (strip_index >= info_ptr->strip_offsets_count)
  {
    goto err_invalid;
  }
  if (((long) info_ptr->strip_offsets[strip_index]) < 0)
  {
    goto err_range;
  }
  offset = (long) (info_ptr->strip_offsets[strip_index] + (row_size * (row_index % info_ptr->rows_per_strip)));
  seek_to_offset(info_ptr, offset, stream);
  if (fread(row_ptr, row_size, 1, stream) != 1)
  {
    goto err_read;
  }
  if (info_ptr->photometric == 0)
  {
    if (bytes_per_sample > 1)
    {
      goto err_unsupported;
    }
    sample_max = (1 << info_ptr->bits_per_sample) - 1;
    for (i = 0; i < row_size; i += 1)
    {
      row_ptr[i] = (unsigned char) (sample_max - row_ptr[i]);
    }

  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_range:
  minitiff_error(info_ptr, msg_err_range);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}

void helper_minitiff_read_info_1(size_t * const count_ref, struct minitiff_info * const info_ptr, FILE * const stream, struct minitiff_getter getter, unsigned long ulvals[4], size_t bits_per_sample_count, unsigned int bits_per_sample_tag_type, long bits_per_sample_offset)
{
  size_t count = *count_ref;
  count = bits_per_sample_count;
  if (count != info_ptr->samples_per_pixel)
  {
    goto err_invalid;
  }
  if (count > 4)
  {
    goto err_unsupported;
  }
  seek_to_offset(info_ptr, bits_per_sample_offset, stream);
  if (read_ulong_values(&getter, bits_per_sample_tag_type, ulvals, count, stream) != count)
  {
    goto err_read;
  }
  while ((--count) > 0)
  {
    if (ulvals[0] != ulvals[count])
    {
      goto err_unsupported;
    }
  }

  info_ptr->bits_per_sample = (unsigned int) ulvals[0];
  *count_ref = count;
}

void helper_minitiff_read_info_2(unsigned long * const ulval_ref, unsigned int * const tag_id_ref, unsigned int * const tag_type_ref, size_t * const count_ref, size_t * const bits_per_sample_count_ref, unsigned int * const bits_per_sample_tag_type_ref, unsigned int * const strip_offsets_tag_type_ref, long * const bits_per_sample_offset_ref, long * const strip_offsets_offset_ref, int * const unknown_metadata_found_ref, struct minitiff_info * const info_ptr, FILE * const stream, struct minitiff_getter getter, unsigned char buf[12], unsigned char * const vbuf)
{
  unsigned long ulval = *ulval_ref;
  unsigned int tag_id = *tag_id_ref;
  unsigned int tag_type = *tag_type_ref;
  size_t count = *count_ref;
  size_t bits_per_sample_count = *bits_per_sample_count_ref;
  unsigned int bits_per_sample_tag_type = *bits_per_sample_tag_type_ref;
  unsigned int strip_offsets_tag_type = *strip_offsets_tag_type_ref;
  long bits_per_sample_offset = *bits_per_sample_offset_ref;
  long strip_offsets_offset = *strip_offsets_offset_ref;
  int unknown_metadata_found = *unknown_metadata_found_ref;
  if (fread(buf, 12, 1, stream) != 1)
  {
    goto err_read;
  }
  tag_id = getter.get_ushort(buf);
  tag_type = getter.get_ushort(buf + 2);
  count = (size_t) getter.get_ulong(buf + 4);
  if (count == 0)
  {
    goto err_unsupported;
  }
  switch (tag_id)
  {
    case MINITIFF_TAG_SUBFILE_TYPE:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      if ((ulval != 0) && (ulval != 1))
      {
        goto err_unsupported;
      }
      break;
    }

    case MINITIFF_TAG_WIDTH:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->width = (size_t) ulval;
      break;
    }

    case MINITIFF_TAG_HEIGHT:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->height = (size_t) ulval;
      break;
    }

    case MINITIFF_TAG_BITS_PER_SAMPLE:
    {
      if (count == 1)
      {
        ulval = get_ulong_value(&getter, tag_type, vbuf);
        info_ptr->bits_per_sample = (unsigned int) ulval;
      }
      else
      {
        bits_per_sample_count = count;
        bits_per_sample_tag_type = tag_type;
        bits_per_sample_offset = (long) getter.get_ulong(vbuf);
      }
      break;
    }

    case MINITIFF_TAG_COMPRESSION:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->compression = (unsigned int) ulval;
      break;
    }

    case MINITIFF_TAG_PHOTOMETRIC:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->photometric = (unsigned int) ulval;
      break;
    }

    case MINITIFF_TAG_STRIP_OFFSETS:
    {
      info_ptr->strip_offsets_count = count;
      if (count == 1)
      {
        if (info_ptr->strip_offsets != 0)
        {
          goto err_invalid;
        }
        info_ptr->strip_offsets = alloc_ulong_array(info_ptr, 1);
        info_ptr->strip_offsets[0] = get_ulong_value(&getter, tag_type, vbuf);
      }
      else
      {
        strip_offsets_tag_type = tag_type;
        strip_offsets_offset = (long) getter.get_ulong(vbuf);
      }
      break;
    }

    case MINITIFF_TAG_ORIENTATION:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->orientation = (unsigned int) ulval;
      break;
    }

    case MINITIFF_TAG_SAMPLES_PER_PIXEL:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->samples_per_pixel = (unsigned int) ulval;
      break;
    }

    case MINITIFF_TAG_ROWS_PER_STRIP:
    {
      if (count != 1)
      {
        goto err_unsupported;
      }
      ulval = get_ulong_value(&getter, tag_type, vbuf);
      info_ptr->rows_per_strip = (size_t) ulval;
      break;
    }

    case MINITIFF_TAG_STRIP_BYTE_COUNTS:
    {
      break;
    }

    case MINITIFF_TAG_PLANAR_CONFIGURATION:

    case MINITIFF_TAG_PREDICTOR:
    {
      if ((count != 1) || (get_ulong_value(&getter, tag_type, vbuf) != 1))
      {
        goto err_unsupported;
      }
      break;
    }

    case MINITIFF_TAG_XMP:

    case MINITIFF_TAG_IPTC:

    case MINITIFF_TAG_EXIF_IFD:

    case MINITIFF_TAG_ICC_PROFILE:

    case MINITIFF_TAG_GPS_IFD:

    case MINITIFF_TAG_INTEROPERABILITY_IFD:

    case MINITIFF_TAG_PRINT_IM:
    {
      if (!unknown_metadata_found)
      {
        unknown_metadata_found = 1;
        minitiff_warning(info_ptr, msg_warn_metadata);
      }
      break;
    }

  }

  *ulval_ref = ulval;
  *tag_id_ref = tag_id;
  *tag_type_ref = tag_type;
  *count_ref = count;
  *bits_per_sample_count_ref = bits_per_sample_count;
  *bits_per_sample_tag_type_ref = bits_per_sample_tag_type;
  *strip_offsets_tag_type_ref = strip_offsets_tag_type;
  *bits_per_sample_offset_ref = bits_per_sample_offset;
  *strip_offsets_offset_ref = strip_offsets_offset;
  *unknown_metadata_found_ref = unknown_metadata_found;
}

