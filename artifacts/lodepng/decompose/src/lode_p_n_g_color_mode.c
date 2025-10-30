typedef struct LodePNGColorMode
{
  LodePNGColorType colortype;
  unsigned bitdepth;
  unsigned char *palette;
  size_t palettesize;
  unsigned key_defined;
  unsigned key_r;
  unsigned key_g;
  unsigned key_b;
} LodePNGColorMode
/*** DEPENDENCIES:
typedef enum LodePNGColorType
{
  LCT_GREY = 0,
  LCT_RGB = 2,
  LCT_PALETTE = 3,
  LCT_GREY_ALPHA = 4,
  LCT_RGBA = 6,
  LCT_MAX_OCTET_VALUE = 255
} LodePNGColorType
----------------------------
***/


