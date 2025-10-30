typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
***/


