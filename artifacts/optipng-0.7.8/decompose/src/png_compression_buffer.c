typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} png_compression_buffer
/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
***/


