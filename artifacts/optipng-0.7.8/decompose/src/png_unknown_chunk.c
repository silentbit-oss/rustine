typedef struct png_unknown_chunk_t
{
  png_byte name[5];
  png_byte *data;
  size_t size;
  png_byte location;
} png_unknown_chunk
/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
***/


