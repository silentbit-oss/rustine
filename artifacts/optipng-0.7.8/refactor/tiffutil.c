#include <minitiff.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiffutil.c>

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
void minitiff_init_info(struct minitiff_info *info_ptr)
{
  memset(info_ptr, 0, sizeof(*info_ptr));
  info_ptr->photometric = (unsigned int) (-1);
}

void minitiff_validate_info(const struct minitiff_info *info_ptr)
{
  if ((info_ptr->width == 0) || (info_ptr->height == 0))
  {
    minitiff_error(info_ptr, "Invalid image dimensions in TIFF file");
  }
  if ((info_ptr->bits_per_sample == 0) || (info_ptr->samples_per_pixel == 0))
  {
    minitiff_error(info_ptr, "Invalid pixel info in TIFF file");
  }
  if ((info_ptr->strip_offsets == 0) || (info_ptr->rows_per_strip == 0))
  {
    minitiff_error(info_ptr, "Invalid strip info in TIFF file");
  }
  if (info_ptr->compression != MINITIFF_COMPRESSION_NONE)
  {
    minitiff_error(info_ptr, "Unsupported compression method in TIFF file");
  }
  if (info_ptr->photometric >= MINITIFF_PHOTOMETRIC_PALETTE)
  {
    minitiff_error(info_ptr, "Unsupported photometric interpretation in TIFF file");
  }
}

void minitiff_destroy_info(struct minitiff_info *info_ptr)
{
  if (info_ptr->strip_offsets != 0)
  {
    free(info_ptr->strip_offsets);
  }
}

static void default_error_handler(const char *msg)
{
  fprintf(stderr, "minitiff: error: %s\n", msg);
  exit(1);
}

void minitiff_error(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->error_handler != 0)
  {
    info_ptr->error_handler(msg);
  }
  else
    default_error_handler(msg);
  abort();
}

static void default_warning_handler(const char *msg)
{
  fprintf(stderr, "minitiff: warning: %s\n", msg);
}

void minitiff_warning(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->warning_handler != 0)
  {
    info_ptr->warning_handler(msg);
  }
  else
    default_warning_handler(msg);
}

const char minitiff_sig_m[4] = {0x4d, 0x4d, 0x00, 0x2a};
const char minitiff_sig_i[4] = {0x49, 0x49, 0x2a, 0x00};
const char minitiff_sig_bigm[4] = {0x4d, 0x4d, 0x00, 0x2b};
const char minitiff_sig_bigi[4] = {0x49, 0x49, 0x2b, 0x00};

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
void minitiff_init_info(struct minitiff_info *info_ptr)
{
  memset(info_ptr, 0, sizeof(*info_ptr));
  info_ptr->photometric = (unsigned int) (-1);
}

void minitiff_validate_info(const struct minitiff_info *info_ptr)
{
  if ((info_ptr->width == 0) || (info_ptr->height == 0))
  {
    minitiff_error(info_ptr, "Invalid image dimensions in TIFF file");
  }
  if ((info_ptr->bits_per_sample == 0) || (info_ptr->samples_per_pixel == 0))
  {
    minitiff_error(info_ptr, "Invalid pixel info in TIFF file");
  }
  if ((info_ptr->strip_offsets == 0) || (info_ptr->rows_per_strip == 0))
  {
    minitiff_error(info_ptr, "Invalid strip info in TIFF file");
  }
  if (info_ptr->compression != MINITIFF_COMPRESSION_NONE)
  {
    minitiff_error(info_ptr, "Unsupported compression method in TIFF file");
  }
  if (info_ptr->photometric >= MINITIFF_PHOTOMETRIC_PALETTE)
  {
    minitiff_error(info_ptr, "Unsupported photometric interpretation in TIFF file");
  }
}

void minitiff_destroy_info(struct minitiff_info *info_ptr)
{
  if (info_ptr->strip_offsets != 0)
  {
    free(info_ptr->strip_offsets);
  }
}

static void default_error_handler(const char *msg)
{
  fprintf(stderr, "minitiff: error: %s\n", msg);
  exit(1);
}

void minitiff_error(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->error_handler != 0)
  {
    info_ptr->error_handler(msg);
  }
  else
    default_error_handler(msg);
  abort();
}

static void default_warning_handler(const char *msg)
{
  fprintf(stderr, "minitiff: warning: %s\n", msg);
}

void minitiff_warning(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->warning_handler != 0)
  {
    info_ptr->warning_handler(msg);
  }
  else
    default_warning_handler(msg);
}

const char minitiff_sig_m[4] = {0x4d, 0x4d, 0x00, 0x2a};
const char minitiff_sig_i[4] = {0x49, 0x49, 0x2a, 0x00};
const char minitiff_sig_bigm[4] = {0x4d, 0x4d, 0x00, 0x2b};
const char minitiff_sig_bigi[4] = {0x49, 0x49, 0x2b, 0x00};
