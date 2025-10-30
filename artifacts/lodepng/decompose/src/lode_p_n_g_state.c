typedef struct LodePNGState
{
  LodePNGDecoderSettings decoder;
  LodePNGEncoderSettings encoder;
  LodePNGColorMode info_raw;
  LodePNGInfo info_png;
  unsigned error;
} LodePNGState
/*** DEPENDENCIES:
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
----------------------------
typedef struct LodePNGEncoderSettings
{
  LodePNGCompressSettings zlibsettings;
  unsigned auto_convert;
  unsigned filter_palette_zero;
  LodePNGFilterStrategy filter_strategy;
  const unsigned char *predefined_filters;
  unsigned force_palette;
  unsigned add_id;
  unsigned text_compression;
} LodePNGEncoderSettings
----------------------------
typedef struct LodePNGDecoderSettings
{
  LodePNGDecompressSettings zlibsettings;
  unsigned ignore_crc;
  unsigned ignore_critical;
  unsigned ignore_end;
  unsigned color_convert;
  unsigned read_text_chunks;
  unsigned remember_unknown_chunks;
  size_t max_text_size;
  size_t max_icc_size;
} LodePNGDecoderSettings
----------------------------
typedef struct LodePNGInfo
{
  unsigned compression_method;
  unsigned filter_method;
  unsigned interlace_method;
  LodePNGColorMode color;
  unsigned background_defined;
  unsigned background_r;
  unsigned background_g;
  unsigned background_b;
  size_t text_num;
  char **text_keys;
  char **text_strings;
  size_t itext_num;
  char **itext_keys;
  char **itext_langtags;
  char **itext_transkeys;
  char **itext_strings;
  unsigned time_defined;
  LodePNGTime time;
  unsigned phys_defined;
  unsigned phys_x;
  unsigned phys_y;
  unsigned phys_unit;
  unsigned gama_defined;
  unsigned gama_gamma;
  unsigned chrm_defined;
  unsigned chrm_white_x;
  unsigned chrm_white_y;
  unsigned chrm_red_x;
  unsigned chrm_red_y;
  unsigned chrm_green_x;
  unsigned chrm_green_y;
  unsigned chrm_blue_x;
  unsigned chrm_blue_y;
  unsigned srgb_defined;
  unsigned srgb_intent;
  unsigned iccp_defined;
  char *iccp_name;
  unsigned char *iccp_profile;
  unsigned iccp_profile_size;
  unsigned sbit_defined;
  unsigned sbit_r;
  unsigned sbit_g;
  unsigned sbit_b;
  unsigned sbit_a;
  unsigned char *unknown_chunks_data[3];
  size_t unknown_chunks_size[3];
} LodePNGInfo
----------------------------
***/


