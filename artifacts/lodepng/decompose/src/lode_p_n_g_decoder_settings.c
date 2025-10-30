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
/*** DEPENDENCIES:
struct LodePNGDecompressSettings
{
  unsigned ignore_adler32;
  unsigned ignore_nlen;
  size_t max_output_size;
  unsigned (*custom_zlib)(unsigned char **, size_t *, const unsigned char *, size_t, const LodePNGDecompressSettings *);
  unsigned (*custom_inflate)(unsigned char **, size_t *, const unsigned char *, size_t, const LodePNGDecompressSettings *);
  const void *custom_context;
}
----------------------------
***/


